#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct skl_clk_rate_cfg_table {int dummy; } ;
struct skl_clk {size_t id; unsigned long rate; TYPE_2__* pdata; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ssp_clks; } ;
struct TYPE_3__ {int /*<<< orphan*/  rate_cfg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  skl_fill_clk_ipc (struct skl_clk_rate_cfg_table*,int) ; 
 int skl_get_clk_type (size_t) ; 
 struct skl_clk_rate_cfg_table* skl_get_rate_cfg (int /*<<< orphan*/ ,unsigned long) ; 
 struct skl_clk* to_skl_clk (struct clk_hw*) ; 

__attribute__((used)) static int skl_clk_set_rate(struct clk_hw *hw, unsigned long rate,
					unsigned long parent_rate)
{
	struct skl_clk *clkdev = to_skl_clk(hw);
	struct skl_clk_rate_cfg_table *rcfg;
	int clk_type;

	if (!rate)
		return -EINVAL;

	rcfg = skl_get_rate_cfg(clkdev->pdata->ssp_clks[clkdev->id].rate_cfg,
							rate);
	if (!rcfg)
		return -EINVAL;

	clk_type = skl_get_clk_type(clkdev->id);
	if (clk_type < 0)
		return clk_type;

	skl_fill_clk_ipc(rcfg, clk_type);
	clkdev->rate = rate;

	return 0;
}