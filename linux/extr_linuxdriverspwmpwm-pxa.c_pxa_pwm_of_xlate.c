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
struct TYPE_2__ {int /*<<< orphan*/  period; } ;
struct pwm_device {TYPE_1__ args; } ;
struct pwm_chip {int dummy; } ;
struct of_phandle_args {int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct pwm_device*) ; 
 struct pwm_device* pwm_request_from_chip (struct pwm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pwm_device *
pxa_pwm_of_xlate(struct pwm_chip *pc, const struct of_phandle_args *args)
{
	struct pwm_device *pwm;

	pwm = pwm_request_from_chip(pc, 0, NULL);
	if (IS_ERR(pwm))
		return pwm;

	pwm->args.period = args->args[0];

	return pwm;
}