#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct skl_clk_data {size_t avail_clk_cnt; TYPE_1__** clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  lookup; } ;

/* Variables and functions */
 int /*<<< orphan*/  clkdev_drop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unregister_src_clk(struct skl_clk_data *dclk)
{
	while (dclk->avail_clk_cnt--)
		clkdev_drop(dclk->clk[dclk->avail_clk_cnt]->lookup);
}