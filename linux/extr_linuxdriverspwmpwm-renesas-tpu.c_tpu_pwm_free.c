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
struct tpu_pwm_device {int dummy; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tpu_pwm_device*) ; 
 struct tpu_pwm_device* pwm_get_chip_data (struct pwm_device*) ; 
 int /*<<< orphan*/  tpu_pwm_timer_stop (struct tpu_pwm_device*) ; 

__attribute__((used)) static void tpu_pwm_free(struct pwm_chip *chip, struct pwm_device *_pwm)
{
	struct tpu_pwm_device *pwm = pwm_get_chip_data(_pwm);

	tpu_pwm_timer_stop(pwm);
	kfree(pwm);
}