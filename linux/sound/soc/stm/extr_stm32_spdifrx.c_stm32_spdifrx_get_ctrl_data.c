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
struct stm32_spdifrx_data {TYPE_1__* pdev; int /*<<< orphan*/  kclk; int /*<<< orphan*/  cs_completion; int /*<<< orphan*/  regmap; int /*<<< orphan*/  ub; int /*<<< orphan*/  cs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  SPDIFRX_CR_CBDMAEN ; 
 int /*<<< orphan*/  SPDIFRX_CS_BYTES_NB ; 
 int /*<<< orphan*/  SPDIFRX_UB_BYTES_NB ; 
 int /*<<< orphan*/  STM32_SPDIFRX_CR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pinctrl_pm_select_default_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pinctrl_pm_select_sleep_state (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stm32_spdifrx_dma_ctrl_start (struct stm32_spdifrx_data*) ; 
 int /*<<< orphan*/  stm32_spdifrx_dma_ctrl_stop (struct stm32_spdifrx_data*) ; 
 int stm32_spdifrx_start_sync (struct stm32_spdifrx_data*) ; 
 int /*<<< orphan*/  stm32_spdifrx_stop (struct stm32_spdifrx_data*) ; 
 scalar_t__ wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_spdifrx_get_ctrl_data(struct stm32_spdifrx_data *spdifrx)
{
	int ret = 0;

	memset(spdifrx->cs, 0, SPDIFRX_CS_BYTES_NB);
	memset(spdifrx->ub, 0, SPDIFRX_UB_BYTES_NB);

	pinctrl_pm_select_default_state(&spdifrx->pdev->dev);

	ret = stm32_spdifrx_dma_ctrl_start(spdifrx);
	if (ret < 0)
		return ret;

	ret = clk_prepare_enable(spdifrx->kclk);
	if (ret) {
		dev_err(&spdifrx->pdev->dev, "Enable kclk failed: %d\n", ret);
		return ret;
	}

	ret = regmap_update_bits(spdifrx->regmap, STM32_SPDIFRX_CR,
				 SPDIFRX_CR_CBDMAEN, SPDIFRX_CR_CBDMAEN);
	if (ret < 0)
		goto end;

	ret = stm32_spdifrx_start_sync(spdifrx);
	if (ret < 0)
		goto end;

	if (wait_for_completion_interruptible_timeout(&spdifrx->cs_completion,
						      msecs_to_jiffies(100))
						      <= 0) {
		dev_dbg(&spdifrx->pdev->dev, "Failed to get control data\n");
		ret = -EAGAIN;
	}

	stm32_spdifrx_stop(spdifrx);
	stm32_spdifrx_dma_ctrl_stop(spdifrx);

end:
	clk_disable_unprepare(spdifrx->kclk);
	pinctrl_pm_select_sleep_state(&spdifrx->pdev->dev);

	return ret;
}