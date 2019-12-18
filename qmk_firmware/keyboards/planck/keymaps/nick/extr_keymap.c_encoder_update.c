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
 scalar_t__ IS_LAYER_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KC_MS_WH_DOWN ; 
 int /*<<< orphan*/  KC_MS_WH_UP ; 
 int /*<<< orphan*/  KC_VOLD ; 
 int /*<<< orphan*/  KC_VOLU ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 

void encoder_update(bool clockwise) {
    if (clockwise && !IS_LAYER_ON(_RAISE)) {
        tap_code(KC_MS_WH_DOWN);
    } else if (!clockwise && !IS_LAYER_ON(_RAISE)) {
        tap_code(KC_MS_WH_UP);
    } else if (clockwise && IS_LAYER_ON(_RAISE)) {
        tap_code(KC_VOLU);
    } else if (!clockwise && IS_LAYER_ON(_RAISE)) {
        tap_code(KC_VOLD);
    }
}