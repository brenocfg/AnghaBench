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
typedef  int /*<<< orphan*/  u16 ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ecap_pwm_chip {TYPE_1__ chip; scalar_t__ mmio_base; } ;
typedef  enum pwm_polarity { ____Placeholder_pwm_polarity } pwm_polarity ;

/* Variables and functions */
 scalar_t__ ECCTL2 ; 
 int /*<<< orphan*/  ECCTL2_APWM_POL_LOW ; 
 int PWM_POLARITY_INVERSED ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 struct ecap_pwm_chip* to_ecap_pwm_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ecap_pwm_set_polarity(struct pwm_chip *chip, struct pwm_device *pwm,
				 enum pwm_polarity polarity)
{
	struct ecap_pwm_chip *pc = to_ecap_pwm_chip(chip);
	u16 value;

	pm_runtime_get_sync(pc->chip.dev);

	value = readw(pc->mmio_base + ECCTL2);

	if (polarity == PWM_POLARITY_INVERSED)
		/* Duty cycle defines LOW period of PWM */
		value |= ECCTL2_APWM_POL_LOW;
	else
		/* Duty cycle defines HIGH period of PWM */
		value &= ~ECCTL2_APWM_POL_LOW;

	writew(value, pc->mmio_base + ECCTL2);

	pm_runtime_put_sync(pc->chip.dev);

	return 0;
}