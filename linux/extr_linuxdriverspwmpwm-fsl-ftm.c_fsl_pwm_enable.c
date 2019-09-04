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
struct fsl_pwm_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTM_OUTMASK ; 
 int fsl_counter_clock_enable (struct fsl_pwm_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_pwm_chip* to_fsl_chip (struct pwm_chip*) ; 

__attribute__((used)) static int fsl_pwm_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct fsl_pwm_chip *fpc = to_fsl_chip(chip);
	int ret;

	mutex_lock(&fpc->lock);
	regmap_update_bits(fpc->regmap, FTM_OUTMASK, BIT(pwm->hwpwm), 0);

	ret = fsl_counter_clock_enable(fpc);
	mutex_unlock(&fpc->lock);

	return ret;
}