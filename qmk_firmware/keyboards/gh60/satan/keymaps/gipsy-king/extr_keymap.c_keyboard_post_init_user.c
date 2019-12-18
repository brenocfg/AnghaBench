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

/* Variables and functions */
 int /*<<< orphan*/  RGBLIGHT_MODE_STATIC_LIGHT ; 
 scalar_t__ cursor_pos ; 
 int /*<<< orphan*/  last_timer ; 
 int /*<<< orphan*/  reset_chars () ; 
 int /*<<< orphan*/  reset_timer ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

void keyboard_post_init_user(void) {
  // reset the bar and animation
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
  cursor_pos = 0;
  reset_chars();
  reset_timer = last_timer = timer_read();
}