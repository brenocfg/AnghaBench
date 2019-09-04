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
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct imx_chip {int /*<<< orphan*/  clk_per; scalar_t__ mmio_base; } ;

/* Variables and functions */
 scalar_t__ MX1_PWMC ; 
 int /*<<< orphan*/  MX1_PWMC_EN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct imx_chip* to_imx_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void imx_pwm_disable_v1(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct imx_chip *imx = to_imx_chip(chip);
	u32 val;

	val = readl(imx->mmio_base + MX1_PWMC);
	val &= ~MX1_PWMC_EN;
	writel(val, imx->mmio_base + MX1_PWMC);

	clk_disable_unprepare(imx->clk_per);
}