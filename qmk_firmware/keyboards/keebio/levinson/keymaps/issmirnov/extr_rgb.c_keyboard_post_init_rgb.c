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
 int /*<<< orphan*/  RGB_CLEAR ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_setrgb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uprintf (char*) ; 

void keyboard_post_init_rgb(void) {
  rgblight_enable();
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
  rgblight_setrgb(RGB_CLEAR);
  uprintf("Reset RGB colors");
}