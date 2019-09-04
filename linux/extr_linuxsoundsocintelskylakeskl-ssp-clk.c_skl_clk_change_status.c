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
struct skl_clk {size_t id; TYPE_1__* pdata; int /*<<< orphan*/  rate; } ;
struct TYPE_4__ {int /*<<< orphan*/  rate_cfg; } ;
struct TYPE_3__ {int /*<<< orphan*/  pvt_data; TYPE_2__* ssp_clks; } ;

/* Variables and functions */
 int EINVAL ; 
 int skl_get_clk_type (size_t) ; 
 struct skl_clk_rate_cfg_table* skl_get_rate_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skl_get_vbus_id (size_t,int) ; 
 int skl_send_clk_dma_control (int /*<<< orphan*/ ,struct skl_clk_rate_cfg_table*,int,int,int) ; 

__attribute__((used)) static int skl_clk_change_status(struct skl_clk *clkdev,
				bool enable)
{
	struct skl_clk_rate_cfg_table *rcfg;
	int vbus_id, clk_type;

	clk_type = skl_get_clk_type(clkdev->id);
	if (clk_type < 0)
		return clk_type;

	vbus_id = skl_get_vbus_id(clkdev->id, clk_type);
	if (vbus_id < 0)
		return vbus_id;

	rcfg = skl_get_rate_cfg(clkdev->pdata->ssp_clks[clkdev->id].rate_cfg,
						clkdev->rate);
	if (!rcfg)
		return -EINVAL;

	return skl_send_clk_dma_control(clkdev->pdata->pvt_data, rcfg,
					vbus_id, clk_type, enable);
}