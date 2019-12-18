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
struct stm32_sai_sub_data {int /*<<< orphan*/  sai_ck; TYPE_1__* pdata; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {struct clk* clk_x11k; struct clk* clk_x8k; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned int SAI_RATE_11K ; 
 int clk_set_parent (int /*<<< orphan*/ ,struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,char*) ; 

__attribute__((used)) static int stm32_sai_set_parent_clock(struct stm32_sai_sub_data *sai,
				      unsigned int rate)
{
	struct platform_device *pdev = sai->pdev;
	struct clk *parent_clk = sai->pdata->clk_x8k;
	int ret;

	if (!(rate % SAI_RATE_11K))
		parent_clk = sai->pdata->clk_x11k;

	ret = clk_set_parent(sai->sai_ck, parent_clk);
	if (ret)
		dev_err(&pdev->dev, " Error %d setting sai_ck parent clock. %s",
			ret, ret == -EBUSY ?
			"Active stream rates conflict\n" : "\n");

	return ret;
}