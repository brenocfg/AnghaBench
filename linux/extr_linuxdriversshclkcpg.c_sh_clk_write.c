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
 int /*<<< orphan*/  iowrite16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_clk_write(int value, struct clk *clk)
{
	if (clk->flags & CLK_ENABLE_REG_8BIT)
		iowrite8(value, clk->mapped_reg);
	else if (clk->flags & CLK_ENABLE_REG_16BIT)
		iowrite16(value, clk->mapped_reg);
	else
		iowrite32(value, clk->mapped_reg);
}