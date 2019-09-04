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
struct TYPE_2__ {scalar_t__ levels; } ;

/* Variables and functions */
 int kbd_get_valid_token_counts () ; 
 TYPE_1__ kbd_info ; 
 int kbd_init_info () ; 
 int /*<<< orphan*/  kbd_init_tokens () ; 
 int kbd_led_present ; 
 int kbd_mode_levels_count ; 

__attribute__((used)) static void kbd_init(void)
{
	int ret;

	ret = kbd_init_info();
	kbd_init_tokens();

	/*
	 * Only supports keyboard backlight when it has at least two modes.
	 */
	if ((ret == 0 && (kbd_info.levels != 0 || kbd_mode_levels_count >= 2))
	    || kbd_get_valid_token_counts() >= 2)
		kbd_led_present = true;
}