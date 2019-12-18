#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_2 ; 
 int /*<<< orphan*/  KC_LOCKING_CAPS ; 
#define  KC_LSHIFT 131 
#define  KC_RSHIFT 130 
 int /*<<< orphan*/  KC_Y ; 
 int MOD_BIT (int const) ; 
 int MOD_MASK_NONE ; 
 int MOD_MASK_SHIFT ; 
#define  NEO2_LMOD3 129 
#define  NEO2_RMOD3 128 
 int /*<<< orphan*/  NEO_3 ; 
 int USB_LED_CAPS_LOCK ; 
 int capslock_state ; 
 int host_keyboard_leds () ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int neo3_state ; 
 int /*<<< orphan*/  neo3_timer ; 
 int process_record_user_shifted (int,TYPE_2__*) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_with_modifiers (int /*<<< orphan*/ ,int) ; 
 int timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LSHIFT:
      if (record->event.pressed) {
        capslock_state |= (MOD_BIT(KC_LSHIFT));
      } else {
        capslock_state &= ~(MOD_BIT(KC_LSHIFT));
      }
      break;
    case KC_RSHIFT:
      if (record->event.pressed) {
        capslock_state |= MOD_BIT(KC_RSHIFT);
      } else {
        capslock_state &= ~(MOD_BIT(KC_RSHIFT));
      }
      break;
    case NEO2_LMOD3:
      if (record->event.pressed) {
        layer_on(NEO_3);
        neo3_state |= (1 << 1);
      } else {
        // Turn off NEO_3 layer unless it's enabled through NEO2_RMOD3 as well.
        if ((neo3_state & ~(1 << 1)) == 0) {
          layer_off(NEO_3);
        }
        neo3_state &= ~(1 << 1);
      }
      break;
    case NEO2_RMOD3:
      if (record->event.pressed) {
        neo3_timer = timer_read();
        neo3_state |= (1 << 2);
        layer_on(NEO_3);
      } else {
        // Turn off NEO_3 layer unless it's enabled through NEO2_LMOD3 as well.
        if ((neo3_state & ~(1 << 2)) == 0) {
          layer_off(NEO_3);
        }
        neo3_state &= ~(1 << 2);

        // Was the NEO2_RMOD3 key TAPPED?
        if (timer_elapsed(neo3_timer) <= 150) {
          if (neo3_state > 0) {
            // We are still in NEO_3 layer, send keycode and modifiers for @
            tap_with_modifiers(KC_2, MOD_MASK_SHIFT);
            return false;
          } else {
            // Do the normal key processing, send y
            tap_with_modifiers(KC_Y, MOD_MASK_NONE);
            return false;
          }
        }
      }
      break;
  }

  if ((capslock_state & MOD_MASK_SHIFT) == MOD_MASK_SHIFT) {
    // CAPSLOCK is currently active, disable it
    if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
      unregister_code(KC_LOCKING_CAPS);
    } else {
      register_code(KC_LOCKING_CAPS);
    }
    return false;
  }

  return process_record_user_shifted(keycode, record);
}