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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct compal_data {long pwm_enable; int curr_pwm; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct compal_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  pwm_disable_control () ; 
 int /*<<< orphan*/  pwm_enable_control () ; 
 int /*<<< orphan*/  set_pwm (int) ; 

__attribute__((used)) static ssize_t pwm_enable_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct compal_data *data = dev_get_drvdata(dev);
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;
	if (val < 0)
		return -EINVAL;

	data->pwm_enable = val;

	switch (val) {
	case 0:  /* Full speed */
		pwm_enable_control();
		set_pwm(255);
		break;
	case 1:  /* As set by pwm1 */
		pwm_enable_control();
		set_pwm(data->curr_pwm);
		break;
	default: /* Control by motherboard */
		pwm_disable_control();
		break;
	}

	return count;
}