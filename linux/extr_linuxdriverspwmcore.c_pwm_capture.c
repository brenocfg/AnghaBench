#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pwm_device {TYPE_2__* chip; } ;
struct pwm_capture {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* capture ) (TYPE_2__*,struct pwm_device*,struct pwm_capture*,unsigned long) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_lock ; 
 int stub1 (TYPE_2__*,struct pwm_device*,struct pwm_capture*,unsigned long) ; 

int pwm_capture(struct pwm_device *pwm, struct pwm_capture *result,
		unsigned long timeout)
{
	int err;

	if (!pwm || !pwm->chip->ops)
		return -EINVAL;

	if (!pwm->chip->ops->capture)
		return -ENOSYS;

	mutex_lock(&pwm_lock);
	err = pwm->chip->ops->capture(pwm->chip, pwm, result, timeout);
	mutex_unlock(&pwm_lock);

	return err;
}