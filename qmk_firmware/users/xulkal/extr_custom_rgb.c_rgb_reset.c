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
 int /*<<< orphan*/  eeconfig_update_rgb_matrix_default () ; 
 int /*<<< orphan*/  eeconfig_update_rgblight_default () ; 
 int /*<<< orphan*/  rgblight_enable () ; 

void rgb_reset(void) {
#if defined(RGB_MATRIX_ENABLE)
    eeconfig_update_rgb_matrix_default();
#elif defined(RGBLIGHT_ENABLE)
    eeconfig_update_rgblight_default();
    rgblight_enable();
#endif
}