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
struct pwm_state {int polarity; } ;
struct pwm_export {int /*<<< orphan*/  lock; struct pwm_device* pwm; } ;
struct pwm_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  enum pwm_polarity { ____Placeholder_pwm_polarity } pwm_polarity ;

/* Variables and functions */
 size_t EINVAL ; 
 int PWM_POLARITY_INVERSED ; 
 int PWM_POLARITY_NORMAL ; 
 struct pwm_export* child_to_pwm_export (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pwm_apply_state (struct pwm_device*,struct pwm_state*) ; 
 int /*<<< orphan*/  pwm_get_state (struct pwm_device*,struct pwm_state*) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 

__attribute__((used)) static ssize_t polarity_store(struct device *child,
			      struct device_attribute *attr,
			      const char *buf, size_t size)
{
	struct pwm_export *export = child_to_pwm_export(child);
	struct pwm_device *pwm = export->pwm;
	enum pwm_polarity polarity;
	struct pwm_state state;
	int ret;

	if (sysfs_streq(buf, "normal"))
		polarity = PWM_POLARITY_NORMAL;
	else if (sysfs_streq(buf, "inversed"))
		polarity = PWM_POLARITY_INVERSED;
	else
		return -EINVAL;

	mutex_lock(&export->lock);
	pwm_get_state(pwm, &state);
	state.polarity = polarity;
	ret = pwm_apply_state(pwm, &state);
	mutex_unlock(&export->lock);

	return ret ? : size;
}