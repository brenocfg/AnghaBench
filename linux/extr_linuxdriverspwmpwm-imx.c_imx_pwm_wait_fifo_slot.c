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
struct pwm_chip {struct device* dev; } ;
struct imx_chip {scalar_t__ mmio_base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MX3_PWMSR ; 
 int MX3_PWMSR_FIFOAV_4WORDS ; 
 int MX3_PWMSR_FIFOAV_MASK ; 
 int /*<<< orphan*/  NSEC_PER_MSEC ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 int /*<<< orphan*/  pwm_get_period (struct pwm_device*) ; 
 int readl (scalar_t__) ; 
 struct imx_chip* to_imx_chip (struct pwm_chip*) ; 

__attribute__((used)) static void imx_pwm_wait_fifo_slot(struct pwm_chip *chip,
				   struct pwm_device *pwm)
{
	struct imx_chip *imx = to_imx_chip(chip);
	struct device *dev = chip->dev;
	unsigned int period_ms;
	int fifoav;
	u32 sr;

	sr = readl(imx->mmio_base + MX3_PWMSR);
	fifoav = sr & MX3_PWMSR_FIFOAV_MASK;
	if (fifoav == MX3_PWMSR_FIFOAV_4WORDS) {
		period_ms = DIV_ROUND_UP(pwm_get_period(pwm),
					 NSEC_PER_MSEC);
		msleep(period_ms);

		sr = readl(imx->mmio_base + MX3_PWMSR);
		if (fifoav == (sr & MX3_PWMSR_FIFOAV_MASK))
			dev_warn(dev, "there is no free FIFO slot\n");
	}
}