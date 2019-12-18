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
struct stm32_sai_sub_data {int /*<<< orphan*/  regmap; TYPE_1__* pdev; } ;
struct stm32_sai_mclk_data {struct stm32_sai_sub_data* sai_data; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAI_XCR1_MCKEN ; 
 int /*<<< orphan*/  STM_SAI_CR1_REGX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stm32_sai_mclk_data* to_mclk_data (struct clk_hw*) ; 

__attribute__((used)) static void stm32_sai_mclk_disable(struct clk_hw *hw)
{
	struct stm32_sai_mclk_data *mclk = to_mclk_data(hw);
	struct stm32_sai_sub_data *sai = mclk->sai_data;

	dev_dbg(&sai->pdev->dev, "Disable master clock\n");

	regmap_update_bits(sai->regmap, STM_SAI_CR1_REGX, SAI_XCR1_MCKEN, 0);
}