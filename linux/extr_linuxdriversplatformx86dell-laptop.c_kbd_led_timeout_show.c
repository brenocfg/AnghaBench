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
typedef  int u8 ;
struct kbd_state {int timeout_value_ac; int timeout_unit_ac; int timeout_value; int timeout_unit; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
#define  KBD_TIMEOUT_DAYS 131 
#define  KBD_TIMEOUT_HOURS 130 
#define  KBD_TIMEOUT_MINUTES 129 
#define  KBD_TIMEOUT_SECONDS 128 
 int kbd_get_state (struct kbd_state*) ; 
 scalar_t__ kbd_timeout_ac_supported ; 
 scalar_t__ power_supply_is_system_supplied () ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t kbd_led_timeout_show(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	struct kbd_state state;
	int value;
	int ret;
	int len;
	u8 unit;

	ret = kbd_get_state(&state);
	if (ret)
		return ret;

	if (kbd_timeout_ac_supported && power_supply_is_system_supplied() > 0) {
		value = state.timeout_value_ac;
		unit = state.timeout_unit_ac;
	} else {
		value = state.timeout_value;
		unit = state.timeout_unit;
	}

	len = sprintf(buf, "%d", value);

	switch (unit) {
	case KBD_TIMEOUT_SECONDS:
		return len + sprintf(buf+len, "s\n");
	case KBD_TIMEOUT_MINUTES:
		return len + sprintf(buf+len, "m\n");
	case KBD_TIMEOUT_HOURS:
		return len + sprintf(buf+len, "h\n");
	case KBD_TIMEOUT_DAYS:
		return len + sprintf(buf+len, "d\n");
	default:
		return -EINVAL;
	}

	return len;
}