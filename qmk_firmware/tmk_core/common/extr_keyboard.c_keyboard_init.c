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
struct TYPE_2__ {int nkro; } ;

/* Variables and functions */
 int /*<<< orphan*/  OLED_ROTATION_0 ; 
 int /*<<< orphan*/  adb_mouse_init () ; 
 int /*<<< orphan*/  backlight_init () ; 
 int /*<<< orphan*/  bootmagic () ; 
 int /*<<< orphan*/  fauxclicky_init () ; 
 int /*<<< orphan*/  keyboard_post_init_kb () ; 
 TYPE_1__ keymap_config ; 
 int /*<<< orphan*/  magic () ; 
 int /*<<< orphan*/  matrix_init () ; 
 int /*<<< orphan*/  oled_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pointing_device_init () ; 
 int /*<<< orphan*/  ps2_mouse_init () ; 
 int /*<<< orphan*/  qwiic_init () ; 
 int /*<<< orphan*/  rgblight_init () ; 
 int /*<<< orphan*/  serial_mouse_init () ; 
 int /*<<< orphan*/  steno_init () ; 
 int /*<<< orphan*/  timer_init () ; 

void keyboard_init(void) {
    timer_init();
    matrix_init();
#ifdef QWIIC_ENABLE
    qwiic_init();
#endif
#ifdef OLED_DRIVER_ENABLE
    oled_init(OLED_ROTATION_0);
#endif
#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_init();
#endif
#ifdef SERIAL_MOUSE_ENABLE
    serial_mouse_init();
#endif
#ifdef ADB_MOUSE_ENABLE
    adb_mouse_init();
#endif
#ifdef BOOTMAGIC_ENABLE
    bootmagic();
#else
    magic();
#endif
#ifdef BACKLIGHT_ENABLE
    backlight_init();
#endif
#ifdef RGBLIGHT_ENABLE
    rgblight_init();
#endif
#ifdef STENO_ENABLE
    steno_init();
#endif
#ifdef FAUXCLICKY_ENABLE
    fauxclicky_init();
#endif
#ifdef POINTING_DEVICE_ENABLE
    pointing_device_init();
#endif
#if defined(NKRO_ENABLE) && defined(FORCE_NKRO)
    keymap_config.nkro = 1;
#endif
    keyboard_post_init_kb(); /* Always keep this last */
}