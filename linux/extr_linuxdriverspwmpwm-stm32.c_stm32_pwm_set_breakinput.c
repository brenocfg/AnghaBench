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
struct stm32_pwm {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TIM_BDTR ; 
 int TIM_BDTR_BK2E ; 
 int TIM_BDTR_BK2F ; 
 int TIM_BDTR_BK2F_SHIFT ; 
 int TIM_BDTR_BK2P ; 
 int TIM_BDTR_BKE ; 
 int TIM_BDTR_BKF ; 
 int TIM_BDTR_BKF_MASK ; 
 int TIM_BDTR_BKF_SHIFT ; 
 int TIM_BDTR_BKP ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int stm32_pwm_set_breakinput(struct stm32_pwm *priv,
				    int index, int level, int filter)
{
	u32 bke = (index == 0) ? TIM_BDTR_BKE : TIM_BDTR_BK2E;
	int shift = (index == 0) ? TIM_BDTR_BKF_SHIFT : TIM_BDTR_BK2F_SHIFT;
	u32 mask = (index == 0) ? TIM_BDTR_BKE | TIM_BDTR_BKP | TIM_BDTR_BKF
				: TIM_BDTR_BK2E | TIM_BDTR_BK2P | TIM_BDTR_BK2F;
	u32 bdtr = bke;

	/*
	 * The both bits could be set since only one will be wrote
	 * due to mask value.
	 */
	if (level)
		bdtr |= TIM_BDTR_BKP | TIM_BDTR_BK2P;

	bdtr |= (filter & TIM_BDTR_BKF_MASK) << shift;

	regmap_update_bits(priv->regmap, TIM_BDTR, mask, bdtr);

	regmap_read(priv->regmap, TIM_BDTR, &bdtr);

	return (bdtr & bke) ? 0 : -EINVAL;
}