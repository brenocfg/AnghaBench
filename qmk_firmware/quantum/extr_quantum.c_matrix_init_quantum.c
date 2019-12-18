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
 int /*<<< orphan*/  OUTPUT_AUTO ; 
 int /*<<< orphan*/  audio_init () ; 
 int /*<<< orphan*/  backlight_init_ports () ; 
 int /*<<< orphan*/  bootmagic_lite () ; 
 int /*<<< orphan*/  dip_switch_init () ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 int /*<<< orphan*/  encoder_init () ; 
 int /*<<< orphan*/  haptic_init () ; 
 int /*<<< orphan*/  led_matrix_init () ; 
 int /*<<< orphan*/  matrix_init_kb () ; 
 int /*<<< orphan*/  rgb_matrix_init () ; 
 int /*<<< orphan*/  set_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unicode_input_mode_init () ; 

void matrix_init_quantum() {
#ifdef BOOTMAGIC_LITE
    bootmagic_lite();
#endif
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
#ifdef BACKLIGHT_ENABLE
#    ifdef LED_MATRIX_ENABLE
    led_matrix_init();
#    else
    backlight_init_ports();
#    endif
#endif
#ifdef AUDIO_ENABLE
    audio_init();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_init();
#endif
#ifdef ENCODER_ENABLE
    encoder_init();
#endif
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE)
    unicode_input_mode_init();
#endif
#ifdef HAPTIC_ENABLE
    haptic_init();
#endif
#ifdef OUTPUT_AUTO_ENABLE
    set_output(OUTPUT_AUTO);
#endif
#ifdef DIP_SWITCH_ENABLE
    dip_switch_init();
#endif

    matrix_init_kb();
}