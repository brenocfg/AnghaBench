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
typedef  int /*<<< orphan*/  u32 ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct img_pwm_chip {int /*<<< orphan*/  periph_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERIP_PWM_PDM_CONTROL ; 
 int PERIP_PWM_PDM_CONTROL_CH_MASK ; 
 int PERIP_PWM_PDM_CONTROL_CH_SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWM_CTRL_CFG ; 
 int /*<<< orphan*/  img_pwm_readl (struct img_pwm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_pwm_writel (struct img_pwm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct img_pwm_chip* to_img_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int img_pwm_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	u32 val;
	struct img_pwm_chip *pwm_chip = to_img_pwm_chip(chip);
	int ret;

	ret = pm_runtime_get_sync(chip->dev);
	if (ret < 0)
		return ret;

	val = img_pwm_readl(pwm_chip, PWM_CTRL_CFG);
	val |= BIT(pwm->hwpwm);
	img_pwm_writel(pwm_chip, PWM_CTRL_CFG, val);

	regmap_update_bits(pwm_chip->periph_regs, PERIP_PWM_PDM_CONTROL,
			   PERIP_PWM_PDM_CONTROL_CH_MASK <<
			   PERIP_PWM_PDM_CONTROL_CH_SHIFT(pwm->hwpwm), 0);

	return 0;
}