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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ IS_LED_ON (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSTR (char*) ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  USB_LED_NUM_LOCK ; 
 int /*<<< orphan*/  USB_LED_SCROLL_LOCK ; 
 int /*<<< orphan*/  host_keyboard_leds () ; 
 int /*<<< orphan*/  oled_write_P (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void render_keyboard_leds(void)
{
    // Host Keyboard LED Status
    uint8_t led_state = host_keyboard_leds();
#ifdef OLED_90ROTATION
    oled_write_P(IS_LED_ON(led_state, USB_LED_NUM_LOCK) ? PSTR("NUMLK") : PSTR("     "), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLK") : PSTR("     "), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLK") : PSTR("     "), false);
#else
    oled_write_P(IS_LED_ON(led_state, USB_LED_NUM_LOCK) ? PSTR("NUM  ") : PSTR("     "), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_CAPS_LOCK) ? PSTR("CAPS ") : PSTR("     "), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRL") : PSTR("    "), false);
#endif
}