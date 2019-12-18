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
 int /*<<< orphan*/  MODERN_DOLCH_RED ; 
 int /*<<< orphan*/  RGBLIGHT_MODE_RAINBOW_SWIRL ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv (int /*<<< orphan*/ ) ; 

void eeconfig_init_keymap(void) {
    rgblight_sethsv(MODERN_DOLCH_RED);
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
}