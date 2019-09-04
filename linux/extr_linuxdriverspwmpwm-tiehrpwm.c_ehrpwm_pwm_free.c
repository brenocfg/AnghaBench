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
struct pwm_device {size_t hwpwm; } ;
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct ehrpwm_pwm_chip {scalar_t__* period_cycles; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ pwm_is_enabled (struct pwm_device*) ; 
 struct ehrpwm_pwm_chip* to_ehrpwm_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static void ehrpwm_pwm_free(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct ehrpwm_pwm_chip *pc = to_ehrpwm_pwm_chip(chip);

	if (pwm_is_enabled(pwm)) {
		dev_warn(chip->dev, "Removing PWM device without disabling\n");
		pm_runtime_put_sync(chip->dev);
	}

	/* set period value to zero on free */
	pc->period_cycles[pwm->hwpwm] = 0;
}