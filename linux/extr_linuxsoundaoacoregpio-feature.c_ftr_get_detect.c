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
struct gpio_runtime {int dummy; } ;
typedef  enum notify_type { ____Placeholder_notify_type } notify_type ;

/* Variables and functions */
#define  AOA_NOTIFY_HEADPHONE 130 
#define  AOA_NOTIFY_LINE_IN 129 
#define  AOA_NOTIFY_LINE_OUT 128 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  PMAC_FTR_READ_GPIO ; 
 int headphone_detect_gpio ; 
 int headphone_detect_gpio_activestate ; 
 int linein_detect_gpio ; 
 int linein_detect_gpio_activestate ; 
 int lineout_detect_gpio ; 
 int lineout_detect_gpio_activestate ; 
 int pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftr_get_detect(struct gpio_runtime *rt,
			  enum notify_type type)
{
	int gpio, ret, active;

	switch (type) {
	case AOA_NOTIFY_HEADPHONE:
		gpio = headphone_detect_gpio;
		active = headphone_detect_gpio_activestate;
		break;
	case AOA_NOTIFY_LINE_IN:
		gpio = linein_detect_gpio;
		active = linein_detect_gpio_activestate;
		break;
	case AOA_NOTIFY_LINE_OUT:
		gpio = lineout_detect_gpio;
		active = lineout_detect_gpio_activestate;
		break;
	default:
		return -EINVAL;
	}

	if (gpio == -1)
		return -ENODEV;

	ret = pmac_call_feature(PMAC_FTR_READ_GPIO, NULL, gpio, 0);
	if (ret < 0)
		return ret;
	return ((ret >> 1) & 1) == active;
}