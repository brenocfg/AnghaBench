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
typedef  int u16 ;
struct led_classdev {int dummy; } ;
struct kbd_state {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ ffs (int) ; 
 scalar_t__ kbd_get_max_level () ; 
 int kbd_get_state (struct kbd_state*) ; 
 scalar_t__ kbd_get_valid_token_counts () ; 
 int kbd_led_level ; 
 int /*<<< orphan*/  kbd_led_mutex ; 
 int kbd_set_level (struct kbd_state*,int) ; 
 int kbd_set_state_safe (struct kbd_state*,struct kbd_state*) ; 
 int kbd_set_token_bit (scalar_t__) ; 
 int kbd_token_bits ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int kbd_led_level_set(struct led_classdev *led_cdev,
			     enum led_brightness value)
{
	enum led_brightness new_value = value;
	struct kbd_state state;
	struct kbd_state new_state;
	u16 num;
	int ret;

	mutex_lock(&kbd_led_mutex);

	if (kbd_get_max_level()) {
		ret = kbd_get_state(&state);
		if (ret)
			goto out;
		new_state = state;
		ret = kbd_set_level(&new_state, value);
		if (ret)
			goto out;
		ret = kbd_set_state_safe(&new_state, &state);
	} else if (kbd_get_valid_token_counts()) {
		for (num = kbd_token_bits; num != 0 && value > 0; --value)
			num &= num - 1; /* clear the first bit set */
		if (num == 0)
			ret = 0;
		else
			ret = kbd_set_token_bit(ffs(num) - 1);
	} else {
		pr_warn("Keyboard brightness level control not supported\n");
		ret = -ENXIO;
	}

out:
	if (ret == 0)
		kbd_led_level = new_value;

	mutex_unlock(&kbd_led_mutex);
	return ret;
}