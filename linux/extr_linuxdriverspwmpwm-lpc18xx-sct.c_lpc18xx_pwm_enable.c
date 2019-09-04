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
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct lpc18xx_pwm_data {unsigned int duty_event; } ;
struct lpc18xx_pwm_chip {unsigned int period_event; } ;
typedef  enum lpc18xx_pwm_res_action { ____Placeholder_lpc18xx_pwm_res_action } lpc18xx_pwm_res_action ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  LPC18XX_PWM_EVCTRL (unsigned int) ; 
 int LPC18XX_PWM_EVCTRL_COMB_MATCH ; 
 int LPC18XX_PWM_EVCTRL_MATCH (unsigned int) ; 
 int /*<<< orphan*/  LPC18XX_PWM_EVSTATEMSK (unsigned int) ; 
 int LPC18XX_PWM_EVSTATEMSK_ALL ; 
 int /*<<< orphan*/  LPC18XX_PWM_OUTPUTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC18XX_PWM_OUTPUTSET (int /*<<< orphan*/ ) ; 
 int LPC18XX_PWM_RES_CLEAR ; 
 int LPC18XX_PWM_RES_SET ; 
 scalar_t__ PWM_POLARITY_NORMAL ; 
 int /*<<< orphan*/  lpc18xx_pwm_set_conflict_res (struct lpc18xx_pwm_chip*,struct pwm_device*,int) ; 
 int /*<<< orphan*/  lpc18xx_pwm_writel (struct lpc18xx_pwm_chip*,int /*<<< orphan*/ ,int) ; 
 struct lpc18xx_pwm_data* pwm_get_chip_data (struct pwm_device*) ; 
 scalar_t__ pwm_get_polarity (struct pwm_device*) ; 
 struct lpc18xx_pwm_chip* to_lpc18xx_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int lpc18xx_pwm_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct lpc18xx_pwm_chip *lpc18xx_pwm = to_lpc18xx_pwm_chip(chip);
	struct lpc18xx_pwm_data *lpc18xx_data = pwm_get_chip_data(pwm);
	enum lpc18xx_pwm_res_action res_action;
	unsigned int set_event, clear_event;

	lpc18xx_pwm_writel(lpc18xx_pwm,
			   LPC18XX_PWM_EVCTRL(lpc18xx_data->duty_event),
			   LPC18XX_PWM_EVCTRL_MATCH(lpc18xx_data->duty_event) |
			   LPC18XX_PWM_EVCTRL_COMB_MATCH);

	lpc18xx_pwm_writel(lpc18xx_pwm,
			   LPC18XX_PWM_EVSTATEMSK(lpc18xx_data->duty_event),
			   LPC18XX_PWM_EVSTATEMSK_ALL);

	if (pwm_get_polarity(pwm) == PWM_POLARITY_NORMAL) {
		set_event = lpc18xx_pwm->period_event;
		clear_event = lpc18xx_data->duty_event;
		res_action = LPC18XX_PWM_RES_SET;
	} else {
		set_event = lpc18xx_data->duty_event;
		clear_event = lpc18xx_pwm->period_event;
		res_action = LPC18XX_PWM_RES_CLEAR;
	}

	lpc18xx_pwm_writel(lpc18xx_pwm, LPC18XX_PWM_OUTPUTSET(pwm->hwpwm),
			   BIT(set_event));
	lpc18xx_pwm_writel(lpc18xx_pwm, LPC18XX_PWM_OUTPUTCL(pwm->hwpwm),
			   BIT(clear_event));
	lpc18xx_pwm_set_conflict_res(lpc18xx_pwm, pwm, res_action);

	return 0;
}