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
 int /*<<< orphan*/  rgblight_mode_noeeprom (int) ; 
 int /*<<< orphan*/  rgblight_savebase () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_goldenrod () ; 

void leader_start(void) {
#ifdef RGBLIGHT_ENABLE
 rgblight_savebase();
 rgblight_mode_noeeprom(1);
 rgblight_sethsv_noeeprom_goldenrod();
#endif
}