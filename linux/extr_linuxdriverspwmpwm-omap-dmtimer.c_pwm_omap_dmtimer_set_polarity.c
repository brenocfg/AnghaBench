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
struct pwm_omap_dmtimer_chip {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dm_timer; TYPE_1__* pdata; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
typedef  enum pwm_polarity { ____Placeholder_pwm_polarity } pwm_polarity ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_pwm ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PWM_OMAP_DMTIMER_TRIGGER_OVERFLOW_AND_COMPARE ; 
 int PWM_POLARITY_INVERSED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct pwm_omap_dmtimer_chip* to_pwm_omap_dmtimer_chip (struct pwm_chip*) ; 

__attribute__((used)) static int pwm_omap_dmtimer_set_polarity(struct pwm_chip *chip,
					 struct pwm_device *pwm,
					 enum pwm_polarity polarity)
{
	struct pwm_omap_dmtimer_chip *omap = to_pwm_omap_dmtimer_chip(chip);

	/*
	 * PWM core will not call set_polarity while PWM is enabled so it's
	 * safe to reconfigure the timer here without stopping it first.
	 */
	mutex_lock(&omap->mutex);
	omap->pdata->set_pwm(omap->dm_timer,
			      polarity == PWM_POLARITY_INVERSED,
			      true,
			      PWM_OMAP_DMTIMER_TRIGGER_OVERFLOW_AND_COMPARE);
	mutex_unlock(&omap->mutex);

	return 0;
}