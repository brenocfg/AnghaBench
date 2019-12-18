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
 int initialized ; 
 int /*<<< orphan*/  rgblight_disable () ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_init () ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_sethsv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void matrix_init_user(void) {
  if (!initialized){
    // Disable to set a known state
    rgblight_disable();
    rgblight_init();
    // None of the subsequent operations take effect if not enabled
    rgblight_enable();
    rgblight_sethsv(0,0,255);
    rgblight_mode(35);
    initialized = 1;
  }
}