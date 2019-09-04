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
struct kbd_state {int /*<<< orphan*/  mode_bit; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int modes; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  KBD_MODE_BIT_ALS ; 
 int /*<<< orphan*/  KBD_MODE_BIT_ON ; 
 int /*<<< orphan*/  KBD_MODE_BIT_TRIGGER ; 
 int /*<<< orphan*/  KBD_MODE_BIT_TRIGGER_ALS ; 
 int kbd_get_state (struct kbd_state*) ; 
 TYPE_1__ kbd_info ; 
 int kbd_is_als_mode_bit (int /*<<< orphan*/ ) ; 
 int kbd_is_trigger_mode_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_led_mutex ; 
 int /*<<< orphan*/  kbd_previous_level ; 
 int /*<<< orphan*/  kbd_previous_mode_bit ; 
 int /*<<< orphan*/  kbd_set_level (struct kbd_state*,int /*<<< orphan*/ ) ; 
 int kbd_set_state_safe (struct kbd_state*,struct kbd_state*) ; 
 scalar_t__ kbd_triggers_supported ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t kbd_led_als_enabled_store(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	struct kbd_state new_state;
	struct kbd_state state;
	bool triggers_enabled = false;
	int enable;
	int ret;

	ret = kstrtoint(buf, 0, &enable);
	if (ret)
		return ret;

	mutex_lock(&kbd_led_mutex);

	ret = kbd_get_state(&state);
	if (ret)
		goto out;

	if (enable == kbd_is_als_mode_bit(state.mode_bit)) {
		ret = count;
		goto out;
	}

	new_state = state;

	if (kbd_triggers_supported)
		triggers_enabled = kbd_is_trigger_mode_bit(state.mode_bit);

	if (enable) {
		if (triggers_enabled)
			new_state.mode_bit = KBD_MODE_BIT_TRIGGER_ALS;
		else
			new_state.mode_bit = KBD_MODE_BIT_ALS;
	} else {
		if (triggers_enabled) {
			new_state.mode_bit = KBD_MODE_BIT_TRIGGER;
			kbd_set_level(&new_state, kbd_previous_level);
		} else {
			new_state.mode_bit = KBD_MODE_BIT_ON;
		}
	}
	if (!(kbd_info.modes & BIT(new_state.mode_bit)))  {
		ret = -EINVAL;
		goto out;
	}

	ret = kbd_set_state_safe(&new_state, &state);
	if (ret)
		goto out;
	kbd_previous_mode_bit = new_state.mode_bit;

	ret = count;
out:
	mutex_unlock(&kbd_led_mutex);
	return ret;
}