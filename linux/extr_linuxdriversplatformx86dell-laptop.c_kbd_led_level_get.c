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
 int ffs (int) ; 
 int kbd_get_first_active_token_bit () ; 
 int kbd_get_level (struct kbd_state*) ; 
 scalar_t__ kbd_get_max_level () ; 
 int kbd_get_state (struct kbd_state*) ; 
 scalar_t__ kbd_get_valid_token_counts () ; 
 int kbd_token_bits ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static enum led_brightness kbd_led_level_get(struct led_classdev *led_cdev)
{
	int ret;
	u16 num;
	struct kbd_state state;

	if (kbd_get_max_level()) {
		ret = kbd_get_state(&state);
		if (ret)
			return 0;
		ret = kbd_get_level(&state);
		if (ret < 0)
			return 0;
		return ret;
	}

	if (kbd_get_valid_token_counts()) {
		ret = kbd_get_first_active_token_bit();
		if (ret < 0)
			return 0;
		for (num = kbd_token_bits; num != 0 && ret > 0; --ret)
			num &= num - 1; /* clear the first bit set */
		if (num == 0)
			return 0;
		return ffs(num) - 1;
	}

	pr_warn("Keyboard brightness level control not supported\n");
	return 0;
}