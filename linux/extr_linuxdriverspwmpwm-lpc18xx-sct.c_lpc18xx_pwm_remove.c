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
struct platform_device {int dummy; } ;
struct lpc18xx_pwm_chip {int /*<<< orphan*/  chip; int /*<<< orphan*/  pwm_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC18XX_PWM_CTRL ; 
 int LPC18XX_PWM_CTRL_HALT ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int lpc18xx_pwm_readl (struct lpc18xx_pwm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc18xx_pwm_writel (struct lpc18xx_pwm_chip*,int /*<<< orphan*/ ,int) ; 
 struct lpc18xx_pwm_chip* platform_get_drvdata (struct platform_device*) ; 
 int pwmchip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc18xx_pwm_remove(struct platform_device *pdev)
{
	struct lpc18xx_pwm_chip *lpc18xx_pwm = platform_get_drvdata(pdev);
	u32 val;

	val = lpc18xx_pwm_readl(lpc18xx_pwm, LPC18XX_PWM_CTRL);
	lpc18xx_pwm_writel(lpc18xx_pwm, LPC18XX_PWM_CTRL,
			   val | LPC18XX_PWM_CTRL_HALT);

	clk_disable_unprepare(lpc18xx_pwm->pwm_clk);

	return pwmchip_remove(&lpc18xx_pwm->chip);
}