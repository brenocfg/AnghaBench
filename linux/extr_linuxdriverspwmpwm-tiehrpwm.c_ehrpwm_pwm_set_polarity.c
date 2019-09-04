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
struct pwm_chip {int dummy; } ;
struct ehrpwm_pwm_chip {int* polarity; } ;
typedef  enum pwm_polarity { ____Placeholder_pwm_polarity } pwm_polarity ;

/* Variables and functions */
 struct ehrpwm_pwm_chip* to_ehrpwm_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int ehrpwm_pwm_set_polarity(struct pwm_chip *chip,
				   struct pwm_device *pwm,
				   enum pwm_polarity polarity)
{
	struct ehrpwm_pwm_chip *pc = to_ehrpwm_pwm_chip(chip);

	/* Configuration of polarity in hardware delayed, do at enable */
	pc->polarity[pwm->hwpwm] = polarity;

	return 0;
}