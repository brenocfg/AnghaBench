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
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_Configured ; 
 int /*<<< orphan*/  SLEEP_MODE_PWR_DOWN ; 
 scalar_t__ USB_DeviceState ; 
 int USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  backlight_set (int /*<<< orphan*/ ) ; 
 scalar_t__ is_backlight_enabled () ; 
 int is_suspended ; 
 int /*<<< orphan*/  led_set (int) ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_disable_noeeprom () ; 
 int /*<<< orphan*/  rgblight_enabled ; 
 int /*<<< orphan*/  rgblight_timer_disable () ; 
 int /*<<< orphan*/  sei () ; 
 int /*<<< orphan*/  set_sleep_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep_cpu () ; 
 int /*<<< orphan*/  sleep_disable () ; 
 int /*<<< orphan*/  sleep_enable () ; 
 int /*<<< orphan*/  suspend_power_down_kb () ; 
 int /*<<< orphan*/  wdt_disable () ; 
 int /*<<< orphan*/  wdt_intr_enable (int) ; 
 int wdt_timeout ; 

__attribute__((used)) static void power_down(uint8_t wdto) {
#    ifdef PROTOCOL_LUFA
    if (USB_DeviceState == DEVICE_STATE_Configured) return;
#    endif
    wdt_timeout = wdto;

    // Watchdog Interrupt Mode
    wdt_intr_enable(wdto);

#    ifdef BACKLIGHT_ENABLE
    backlight_set(0);
#    endif

    // Turn off LED indicators
    uint8_t leds_off = 0;
#    if defined(BACKLIGHT_CAPS_LOCK) && defined(BACKLIGHT_ENABLE)
    if (is_backlight_enabled()) {
        // Don't try to turn off Caps Lock indicator as it is backlight and backlight is already off
        leds_off |= (1 << USB_LED_CAPS_LOCK);
    }
#    endif
    led_set(leds_off);

#    ifdef AUDIO_ENABLE
    // This sometimes disables the start-up noise, so it's been disabled
    // stop_all_notes();
#    endif /* AUDIO_ENABLE */
#    if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
#        ifdef RGBLIGHT_ANIMATIONS
    rgblight_timer_disable();
#        endif
    if (!is_suspended) {
        is_suspended     = true;
        rgblight_enabled = rgblight_config.enable;
        rgblight_disable_noeeprom();
    }
#    endif
    suspend_power_down_kb();

    // TODO: more power saving
    // See PicoPower application note
    // - I/O port input with pullup
    // - prescale clock
    // - BOD disable
    // - Power Reduction Register PRR
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();

    // Disable watchdog after sleep
    wdt_disable();
}