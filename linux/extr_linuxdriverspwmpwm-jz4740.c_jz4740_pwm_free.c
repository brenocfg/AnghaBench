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

/* Variables and functions */
 int /*<<< orphan*/  jz4740_timer_set_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_timer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jz4740_pwm_free(struct pwm_chip *chip, struct pwm_device *pwm)
{
	jz4740_timer_set_ctrl(pwm->hwpwm, 0);

	jz4740_timer_stop(pwm->hwpwm);
}