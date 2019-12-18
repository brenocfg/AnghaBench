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
 int /*<<< orphan*/  KC_LGUI ; 
 int is_lgui_active ; 
 int /*<<< orphan*/  lgui_timer ; 
 int timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void matrix_scan_user(void) { 
  if (is_lgui_active) {
    if (timer_elapsed(lgui_timer) > 1000) {
      unregister_code(KC_LGUI);
      is_lgui_active = false;
    }
  }
}