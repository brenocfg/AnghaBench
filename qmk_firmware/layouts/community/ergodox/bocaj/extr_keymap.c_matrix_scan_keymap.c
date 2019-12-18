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
typedef  int uint8_t ;

/* Variables and functions */
 int MODS_ALT_MASK ; 
 int MODS_CTRL_MASK ; 
 int MODS_GUI_MASK ; 
 int MODS_SHIFT_MASK ; 
 int USB_LED_CAPS_LOCK ; 
#define  _ADJUST 133 
#define  _DIABLO 132 
#define  _LOWER 131 
#define  _QWERTY 130 
#define  _WINWORKMAN 129 
#define  _WORKMAN 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ergodox_board_led_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_on () ; 
 int /*<<< orphan*/  ergodox_right_led_1_set (int) ; 
 int /*<<< orphan*/  ergodox_right_led_2_off () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_2_set (int) ; 
 int /*<<< orphan*/  ergodox_right_led_3_off () ; 
 int /*<<< orphan*/  ergodox_right_led_3_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_set (int) ; 
 int get_mods () ; 
 int get_oneshot_mods () ; 
 int host_keyboard_leds () ; 
 int /*<<< orphan*/  layer_state ; 

void matrix_scan_keymap(void) {
  uint8_t modifiers = get_mods();
  uint8_t led_usb_state = host_keyboard_leds();
  uint8_t one_shot = get_oneshot_mods();
  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  switch (layer) {
    case _WORKMAN:
    case _QWERTY:
    case _WINWORKMAN:
      if (modifiers & MODS_SHIFT_MASK || led_usb_state & (1<<USB_LED_CAPS_LOCK) || one_shot & MODS_SHIFT_MASK) {
        ergodox_right_led_1_on();
        ergodox_right_led_1_set( 25 );
      }
      if (modifiers & MODS_CTRL_MASK || one_shot & MODS_CTRL_MASK || modifiers & MODS_GUI_MASK || one_shot & MODS_GUI_MASK) {
        if ((modifiers & MODS_CTRL_MASK || one_shot & MODS_CTRL_MASK) && (modifiers & MODS_GUI_MASK || one_shot & MODS_GUI_MASK)) {
          ergodox_right_led_2_on();
          ergodox_right_led_2_set( 50 );
        } else {
          ergodox_right_led_2_on();
          ergodox_right_led_2_set( 10 );
        }
      }
      if (modifiers & MODS_ALT_MASK || one_shot & MODS_ALT_MASK) {
        ergodox_right_led_3_on();
        ergodox_right_led_3_set( 10 );
      }
      break;
    case _LOWER:
      ergodox_right_led_3_on();
      ergodox_right_led_3_set(10); // Default brightness is deadly in a dark room
      break;
    case _ADJUST:
      ergodox_right_led_2_on();
      ergodox_right_led_2_set(10);
      break;
    case _DIABLO:
      ergodox_right_led_1_on();
      ergodox_right_led_1_set(10);
      break;
    default:
      // none
      break;
  }
}