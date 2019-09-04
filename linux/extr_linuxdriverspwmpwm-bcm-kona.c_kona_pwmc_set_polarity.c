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
struct pwm_device {unsigned int hwpwm; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct kona_pwmc {int /*<<< orphan*/  clk; scalar_t__ base; } ;
typedef  enum pwm_polarity { ____Placeholder_pwm_polarity } pwm_polarity ;

/* Variables and functions */
 scalar_t__ PWM_CONTROL_OFFSET ; 
 int PWM_CONTROL_POLARITY_SHIFT (unsigned int) ; 
 int PWM_POLARITY_NORMAL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kona_pwmc_apply_settings (struct kona_pwmc*,unsigned int) ; 
 int /*<<< orphan*/  kona_pwmc_prepare_for_settings (struct kona_pwmc*,unsigned int) ; 
 unsigned int readl (scalar_t__) ; 
 struct kona_pwmc* to_kona_pwmc (struct pwm_chip*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int kona_pwmc_set_polarity(struct pwm_chip *chip, struct pwm_device *pwm,
				  enum pwm_polarity polarity)
{
	struct kona_pwmc *kp = to_kona_pwmc(chip);
	unsigned int chan = pwm->hwpwm;
	unsigned int value;
	int ret;

	ret = clk_prepare_enable(kp->clk);
	if (ret < 0) {
		dev_err(chip->dev, "failed to enable clock: %d\n", ret);
		return ret;
	}

	kona_pwmc_prepare_for_settings(kp, chan);

	value = readl(kp->base + PWM_CONTROL_OFFSET);

	if (polarity == PWM_POLARITY_NORMAL)
		value |= 1 << PWM_CONTROL_POLARITY_SHIFT(chan);
	else
		value &= ~(1 << PWM_CONTROL_POLARITY_SHIFT(chan));

	writel(value, kp->base + PWM_CONTROL_OFFSET);

	kona_pwmc_apply_settings(kp, chan);

	clk_disable_unprepare(kp->clk);

	return 0;
}