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
struct pwm_state {unsigned int duty_cycle; } ;
struct pwm_export {int /*<<< orphan*/  lock; struct pwm_device* pwm; } ;
struct pwm_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct pwm_export* child_to_pwm_export (struct device*) ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pwm_apply_state (struct pwm_device*,struct pwm_state*) ; 
 int /*<<< orphan*/  pwm_get_state (struct pwm_device*,struct pwm_state*) ; 

__attribute__((used)) static ssize_t duty_cycle_store(struct device *child,
				struct device_attribute *attr,
				const char *buf, size_t size)
{
	struct pwm_export *export = child_to_pwm_export(child);
	struct pwm_device *pwm = export->pwm;
	struct pwm_state state;
	unsigned int val;
	int ret;

	ret = kstrtouint(buf, 0, &val);
	if (ret)
		return ret;

	mutex_lock(&export->lock);
	pwm_get_state(pwm, &state);
	state.duty_cycle = val;
	ret = pwm_apply_state(pwm, &state);
	mutex_unlock(&export->lock);

	return ret ? : size;
}