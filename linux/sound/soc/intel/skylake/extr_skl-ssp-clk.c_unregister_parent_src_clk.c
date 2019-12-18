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
struct skl_clk_parent {int /*<<< orphan*/  hw; int /*<<< orphan*/  lookup; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_hw_unregister_fixed_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdev_drop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unregister_parent_src_clk(struct skl_clk_parent *pclk,
					unsigned int id)
{
	while (id--) {
		clkdev_drop(pclk[id].lookup);
		clk_hw_unregister_fixed_rate(pclk[id].hw);
	}
}