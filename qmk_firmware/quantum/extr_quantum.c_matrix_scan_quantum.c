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
 int /*<<< orphan*/  backlight_task () ; 
 int /*<<< orphan*/  dip_switch_read (int) ; 
 int /*<<< orphan*/  encoder_read () ; 
 int /*<<< orphan*/  haptic_task () ; 
 int /*<<< orphan*/  led_matrix_task () ; 
 int /*<<< orphan*/  matrix_scan_combo () ; 
 int /*<<< orphan*/  matrix_scan_kb () ; 
 int /*<<< orphan*/  matrix_scan_music () ; 
 int /*<<< orphan*/  matrix_scan_tap_dance () ; 
 int /*<<< orphan*/  rgb_matrix_task () ; 

void matrix_scan_quantum() {
#if defined(AUDIO_ENABLE) && !defined(NO_MUSIC_MODE)
    matrix_scan_music();
#endif

#ifdef TAP_DANCE_ENABLE
    matrix_scan_tap_dance();
#endif

#ifdef COMBO_ENABLE
    matrix_scan_combo();
#endif

#if defined(BACKLIGHT_ENABLE)
#    if defined(LED_MATRIX_ENABLE)
    led_matrix_task();
#    elif defined(BACKLIGHT_PIN) || defined(BACKLIGHT_PINS)
    backlight_task();
#    endif
#endif

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_task();
#endif

#ifdef ENCODER_ENABLE
    encoder_read();
#endif

#ifdef HAPTIC_ENABLE
    haptic_task();
#endif

#ifdef DIP_SWITCH_ENABLE
    dip_switch_read(false);
#endif

    matrix_scan_kb();
}