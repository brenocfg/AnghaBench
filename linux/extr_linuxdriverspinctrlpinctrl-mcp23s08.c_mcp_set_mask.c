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
typedef  int u16 ;
struct mcp23s08 {unsigned int reg_shift; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int mcp_set_mask(struct mcp23s08 *mcp, unsigned int reg,
		       unsigned int mask, bool enabled)
{
	u16 val  = enabled ? 0xffff : 0x0000;
	return regmap_update_bits(mcp->regmap, reg << mcp->reg_shift,
				  mask, val);
}