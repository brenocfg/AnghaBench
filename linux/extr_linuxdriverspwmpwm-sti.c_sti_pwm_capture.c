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
struct sti_pwm_compat_data {scalar_t__ cpt_num_devs; } ;
struct sti_pwm_chip {int /*<<< orphan*/  pwm_cpt_en; int /*<<< orphan*/  cpt_clk; int /*<<< orphan*/  regmap; int /*<<< orphan*/  pwm_cpt_int_en; struct device* dev; struct sti_pwm_compat_data* cdata; } ;
struct sti_cpt_ddata {int index; unsigned long long* snapshot; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; } ;
struct pwm_device {scalar_t__ hwpwm; } ;
struct pwm_chip {int dummy; } ;
struct pwm_capture {unsigned long long period; unsigned long long duty_cycle; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int /*<<< orphan*/  CPT_EDGE_DISABLED ; 
 int /*<<< orphan*/  CPT_EDGE_RISING ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 unsigned long long NSEC_PER_SEC ; 
 int /*<<< orphan*/  PWM_CPT_EDGE (scalar_t__) ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sti_cpt_ddata* pwm_get_chip_data (struct pwm_device*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sti_pwm_chip* to_sti_pwmchip (struct pwm_chip*) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sti_pwm_capture(struct pwm_chip *chip, struct pwm_device *pwm,
			   struct pwm_capture *result, unsigned long timeout)
{
	struct sti_pwm_chip *pc = to_sti_pwmchip(chip);
	struct sti_pwm_compat_data *cdata = pc->cdata;
	struct sti_cpt_ddata *ddata = pwm_get_chip_data(pwm);
	struct device *dev = pc->dev;
	unsigned int effective_ticks;
	unsigned long long high, low;
	int ret;

	if (pwm->hwpwm >= cdata->cpt_num_devs) {
		dev_err(dev, "device %u is not valid\n", pwm->hwpwm);
		return -EINVAL;
	}

	mutex_lock(&ddata->lock);
	ddata->index = 0;

	/* Prepare capture measurement */
	regmap_write(pc->regmap, PWM_CPT_EDGE(pwm->hwpwm), CPT_EDGE_RISING);
	regmap_field_write(pc->pwm_cpt_int_en, BIT(pwm->hwpwm));

	/* Enable capture */
	ret = regmap_field_write(pc->pwm_cpt_en, 1);
	if (ret) {
		dev_err(dev, "failed to enable PWM capture %u: %d\n",
			pwm->hwpwm, ret);
		goto out;
	}

	ret = wait_event_interruptible_timeout(ddata->wait, ddata->index > 1,
					       msecs_to_jiffies(timeout));

	regmap_write(pc->regmap, PWM_CPT_EDGE(pwm->hwpwm), CPT_EDGE_DISABLED);

	if (ret == -ERESTARTSYS)
		goto out;

	switch (ddata->index) {
	case 0:
	case 1:
		/*
		 * Getting here could mean:
		 *  - input signal is constant of less than 1 Hz
		 *  - there is no input signal at all
		 *
		 * In such case the frequency is rounded down to 0
		 */
		result->period = 0;
		result->duty_cycle = 0;

		break;

	case 2:
		/* We have everying we need */
		high = ddata->snapshot[1] - ddata->snapshot[0];
		low = ddata->snapshot[2] - ddata->snapshot[1];

		effective_ticks = clk_get_rate(pc->cpt_clk);

		result->period = (high + low) * NSEC_PER_SEC;
		result->period /= effective_ticks;

		result->duty_cycle = high * NSEC_PER_SEC;
		result->duty_cycle /= effective_ticks;

		break;

	default:
		dev_err(dev, "internal error\n");
		break;
	}

out:
	/* Disable capture */
	regmap_field_write(pc->pwm_cpt_en, 0);

	mutex_unlock(&ddata->lock);
	return ret;
}