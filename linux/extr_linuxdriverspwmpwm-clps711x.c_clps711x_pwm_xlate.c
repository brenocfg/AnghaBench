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
struct pwm_chip {scalar_t__ npwm; } ;
struct of_phandle_args {scalar_t__* args; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct pwm_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct pwm_device* pwm_request_from_chip (struct pwm_chip*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pwm_device *clps711x_pwm_xlate(struct pwm_chip *chip,
					     const struct of_phandle_args *args)
{
	if (args->args[0] >= chip->npwm)
		return ERR_PTR(-EINVAL);

	return pwm_request_from_chip(chip, args->args[0], NULL);
}