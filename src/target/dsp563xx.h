/***************************************************************************
 *   Copyright (C) 2009-2011 by Mathias Kuester                            *
 *   mkdorg@users.sourceforge.net                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef DSP563XX_H
#define DSP563XX_H

#include <jtag/jtag.h>
#include <target/dsp563xx_once.h>

#define DSP563XX_NUMCOREREGS	54
#define DSP563XX_NUMONCEREGS	25

struct mcu_jtag {
	struct jtag_tap *tap;
};

struct dsp563xx_common {
	struct mcu_jtag jtag_info;
	struct reg_cache *core_cache;
	uint32_t core_regs[DSP563XX_NUMCOREREGS];
	struct once_reg once_regs[DSP563XX_NUMONCEREGS];

	/* register cache to processor synchronization */
	int (*read_core_reg) (struct target *target, int num);
	int (*write_core_reg) (struct target *target, int num);
};

struct dsp563xx_core_reg {
	uint32_t num;
	const char *name;
	uint32_t size;
	uint8_t eame;
	uint32_t instr_mask;
	struct target *target;
	struct dsp563xx_common *dsp563xx_common;
};

static inline struct dsp563xx_common *target_to_dsp563xx(struct target *target)
{
	return target->arch_info;
}

#endif /* DSP563XX_H */
