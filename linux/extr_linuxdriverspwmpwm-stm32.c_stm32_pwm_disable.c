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
struct stm32_pwm {int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; scalar_t__ have_complementary_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIM_CCER ; 
 int TIM_CCER_CC1E ; 
 int TIM_CCER_CC1NE ; 
 int /*<<< orphan*/  TIM_CR1 ; 
 int TIM_CR1_CEN ; 
 int /*<<< orphan*/  active_channels (struct stm32_pwm*) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_pwm_disable(struct stm32_pwm *priv, int ch)
{
	u32 mask;

	/* Disable channel */
	mask = TIM_CCER_CC1E << (ch * 4);
	if (priv->have_complementary_output)
		mask |= TIM_CCER_CC1NE << (ch * 4);

	regmap_update_bits(priv->regmap, TIM_CCER, mask, 0);

	/* When all channels are disabled, we can disable the controller */
	if (!active_channels(priv))
		regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, 0);

	clk_disable(priv->clk);
}