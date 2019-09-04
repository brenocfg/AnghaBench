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
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct atmel_tcb_pwm_device {int polarity; } ;
typedef  enum pwm_polarity { ____Placeholder_pwm_polarity } pwm_polarity ;

/* Variables and functions */
 struct atmel_tcb_pwm_device* pwm_get_chip_data (struct pwm_device*) ; 

__attribute__((used)) static int atmel_tcb_pwm_set_polarity(struct pwm_chip *chip,
				      struct pwm_device *pwm,
				      enum pwm_polarity polarity)
{
	struct atmel_tcb_pwm_device *tcbpwm = pwm_get_chip_data(pwm);

	tcbpwm->polarity = polarity;

	return 0;
}