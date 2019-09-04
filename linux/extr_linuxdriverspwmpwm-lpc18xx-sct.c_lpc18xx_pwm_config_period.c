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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct pwm_chip {int dummy; } ;
struct lpc18xx_pwm_chip {int clk_rate; int /*<<< orphan*/  period_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC18XX_PWM_MATCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC18XX_PWM_MATCHREL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc18xx_pwm_writel (struct lpc18xx_pwm_chip*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct lpc18xx_pwm_chip* to_lpc18xx_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static void lpc18xx_pwm_config_period(struct pwm_chip *chip, int period_ns)
{
	struct lpc18xx_pwm_chip *lpc18xx_pwm = to_lpc18xx_pwm_chip(chip);
	u64 val;

	val = (u64)period_ns * lpc18xx_pwm->clk_rate;
	do_div(val, NSEC_PER_SEC);

	lpc18xx_pwm_writel(lpc18xx_pwm,
			   LPC18XX_PWM_MATCH(lpc18xx_pwm->period_event),
			   (u32)val - 1);

	lpc18xx_pwm_writel(lpc18xx_pwm,
			   LPC18XX_PWM_MATCHREL(lpc18xx_pwm->period_event),
			   (u32)val - 1);
}