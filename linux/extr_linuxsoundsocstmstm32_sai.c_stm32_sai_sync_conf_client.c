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
struct stm32_sai_data {int /*<<< orphan*/  pclk; int /*<<< orphan*/  base; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SAI_GCR_SYNCIN_MASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_sai_sync_conf_client(struct stm32_sai_data *sai, int synci)
{
	int ret;

	/* Enable peripheral clock to allow GCR register access */
	ret = clk_prepare_enable(sai->pclk);
	if (ret) {
		dev_err(&sai->pdev->dev, "failed to enable clock: %d\n", ret);
		return ret;
	}

	writel_relaxed(FIELD_PREP(SAI_GCR_SYNCIN_MASK, (synci - 1)), sai->base);

	clk_disable_unprepare(sai->pclk);

	return 0;
}