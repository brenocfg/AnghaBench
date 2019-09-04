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
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct imx_chip {scalar_t__ mmio_base; } ;

/* Variables and functions */
 scalar_t__ MX1_PWMP ; 
 scalar_t__ MX1_PWMS ; 
 int readl (scalar_t__) ; 
 struct imx_chip* to_imx_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int imx_pwm_config_v1(struct pwm_chip *chip,
		struct pwm_device *pwm, int duty_ns, int period_ns)
{
	struct imx_chip *imx = to_imx_chip(chip);

	/*
	 * The PWM subsystem allows for exact frequencies. However,
	 * I cannot connect a scope on my device to the PWM line and
	 * thus cannot provide the program the PWM controller
	 * exactly. Instead, I'm relying on the fact that the
	 * Bootloader (u-boot or WinCE+haret) has programmed the PWM
	 * function group already. So I'll just modify the PWM sample
	 * register to follow the ratio of duty_ns vs. period_ns
	 * accordingly.
	 *
	 * This is good enough for programming the brightness of
	 * the LCD backlight.
	 *
	 * The real implementation would divide PERCLK[0] first by
	 * both the prescaler (/1 .. /128) and then by CLKSEL
	 * (/2 .. /16).
	 */
	u32 max = readl(imx->mmio_base + MX1_PWMP);
	u32 p = max * duty_ns / period_ns;
	writel(max - p, imx->mmio_base + MX1_PWMS);

	return 0;
}