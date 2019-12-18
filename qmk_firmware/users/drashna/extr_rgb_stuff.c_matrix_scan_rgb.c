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
struct TYPE_2__ {scalar_t__ rgb_matrix_idle_anim; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGB_MATRIX_REST_MODE ; 
 scalar_t__ RGB_MATRIX_TYPING_HEATMAP ; 
 int /*<<< orphan*/  hypno_timer ; 
 int /*<<< orphan*/  matrix_scan_indicator () ; 
 scalar_t__ rgb_matrix_get_mode () ; 
 int /*<<< orphan*/  rgb_matrix_mode_noeeprom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_rgblight_fadeout () ; 
 int timer_elapsed32 (int /*<<< orphan*/ ) ; 
 TYPE_1__ userspace_config ; 

void matrix_scan_rgb(void) {
#ifdef RGBLIGHT_ENABLE
#    ifdef RGBLIGHT_TWINKLE
    scan_rgblight_fadeout();
#    endif  // RGBLIGHT_ENABLE

#    ifdef INDICATOR_LIGHTS
    matrix_scan_indicator();
#    endif
#endif

#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    if (userspace_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == RGB_MATRIX_TYPING_HEATMAP && timer_elapsed32(hypno_timer) > 15000) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_REST_MODE);
    }
#endif
}