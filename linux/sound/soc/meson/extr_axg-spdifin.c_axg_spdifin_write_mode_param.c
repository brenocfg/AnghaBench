#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int uint64_t ;
struct regmap {int dummy; } ;

/* Variables and functions */
 unsigned int GENMASK (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int do_div (unsigned int,unsigned int) ; 
 unsigned int regmap_get_reg_stride (struct regmap*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void axg_spdifin_write_mode_param(struct regmap *map, int mode,
					 unsigned int val,
					 unsigned int num_per_reg,
					 unsigned int base_reg,
					 unsigned int width)
{
	uint64_t offset = mode;
	unsigned int reg, shift, rem;

	rem = do_div(offset, num_per_reg);

	reg = offset * regmap_get_reg_stride(map) + base_reg;
	shift = width * (num_per_reg - 1 - rem);

	regmap_update_bits(map, reg, GENMASK(width - 1, 0) << shift,
			   val << shift);
}