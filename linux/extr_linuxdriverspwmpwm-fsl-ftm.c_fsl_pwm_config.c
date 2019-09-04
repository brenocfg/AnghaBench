#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct fsl_pwm_chip {int period_ns; int /*<<< orphan*/  regmap; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk_ps; TYPE_1__ chip; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  FTM_CSC (int /*<<< orphan*/ ) ; 
 int FTM_CSC_ELSB ; 
 int FTM_CSC_MSB ; 
 int /*<<< orphan*/  FTM_CV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTM_MOD ; 
 int /*<<< orphan*/  FTM_SC ; 
 int /*<<< orphan*/  FTM_SC_PS_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int fsl_pwm_calculate_duty (struct fsl_pwm_chip*,int,int) ; 
 int fsl_pwm_calculate_period (struct fsl_pwm_chip*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct fsl_pwm_chip* to_fsl_chip (struct pwm_chip*) ; 

__attribute__((used)) static int fsl_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			  int duty_ns, int period_ns)
{
	struct fsl_pwm_chip *fpc = to_fsl_chip(chip);
	u32 period, duty;

	mutex_lock(&fpc->lock);

	/*
	 * The Freescale FTM controller supports only a single period for
	 * all PWM channels, therefore incompatible changes need to be
	 * refused.
	 */
	if (fpc->period_ns && fpc->period_ns != period_ns) {
		dev_err(fpc->chip.dev,
			"conflicting period requested for PWM %u\n",
			pwm->hwpwm);
		mutex_unlock(&fpc->lock);
		return -EBUSY;
	}

	if (!fpc->period_ns && duty_ns) {
		period = fsl_pwm_calculate_period(fpc, period_ns);
		if (!period) {
			dev_err(fpc->chip.dev, "failed to calculate period\n");
			mutex_unlock(&fpc->lock);
			return -EINVAL;
		}

		regmap_update_bits(fpc->regmap, FTM_SC, FTM_SC_PS_MASK,
				   fpc->clk_ps);
		regmap_write(fpc->regmap, FTM_MOD, period - 1);

		fpc->period_ns = period_ns;
	}

	mutex_unlock(&fpc->lock);

	duty = fsl_pwm_calculate_duty(fpc, period_ns, duty_ns);

	regmap_write(fpc->regmap, FTM_CSC(pwm->hwpwm),
		     FTM_CSC_MSB | FTM_CSC_ELSB);
	regmap_write(fpc->regmap, FTM_CV(pwm->hwpwm), duty);

	return 0;
}