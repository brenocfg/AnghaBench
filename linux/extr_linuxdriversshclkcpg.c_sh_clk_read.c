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
struct clk {int flags; int /*<<< orphan*/  mapped_reg; } ;

/* Variables and functions */
 int CLK_ENABLE_REG_16BIT ; 
 int CLK_ENABLE_REG_8BIT ; 
 unsigned int ioread16 (int /*<<< orphan*/ ) ; 
 unsigned int ioread32 (int /*<<< orphan*/ ) ; 
 unsigned int ioread8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int sh_clk_read(struct clk *clk)
{
	if (clk->flags & CLK_ENABLE_REG_8BIT)
		return ioread8(clk->mapped_reg);
	else if (clk->flags & CLK_ENABLE_REG_16BIT)
		return ioread16(clk->mapped_reg);

	return ioread32(clk->mapped_reg);
}