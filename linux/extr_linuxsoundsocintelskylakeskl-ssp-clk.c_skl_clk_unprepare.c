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
struct skl_clk {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skl_clk_change_status (struct skl_clk*,int) ; 
 struct skl_clk* to_skl_clk (struct clk_hw*) ; 

__attribute__((used)) static void skl_clk_unprepare(struct clk_hw *hw)
{
	struct skl_clk *clkdev = to_skl_clk(hw);

	skl_clk_change_status(clkdev, false);
}