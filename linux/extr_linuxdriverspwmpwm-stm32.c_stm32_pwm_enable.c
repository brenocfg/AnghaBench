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
typedef  int u32 ;
struct stm32_pwm {int /*<<< orphan*/  regmap; scalar_t__ have_complementary_output; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIM_CCER ; 
 int TIM_CCER_CC1E ; 
 int TIM_CCER_CC1NE ; 
 int /*<<< orphan*/  TIM_CR1 ; 
 int TIM_CR1_CEN ; 
 int /*<<< orphan*/  TIM_EGR ; 
 int TIM_EGR_UG ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int stm32_pwm_enable(struct stm32_pwm *priv, int ch)
{
	u32 mask;
	int ret;

	ret = clk_enable(priv->clk);
	if (ret)
		return ret;

	/* Enable channel */
	mask = TIM_CCER_CC1E << (ch * 4);
	if (priv->have_complementary_output)
		mask |= TIM_CCER_CC1NE << (ch * 4);

	regmap_update_bits(priv->regmap, TIM_CCER, mask, mask);

	/* Make sure that registers are updated */
	regmap_update_bits(priv->regmap, TIM_EGR, TIM_EGR_UG, TIM_EGR_UG);

	/* Enable controller */
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, TIM_CR1_CEN);

	return 0;
}