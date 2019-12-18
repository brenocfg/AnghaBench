#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_8__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  RESET 130 
#define  RGBRST 129 
#define  RGB_TOG 128 
 int /*<<< orphan*/  process_custom_tap_dance (int,TYPE_2__*) ; 
 scalar_t__ process_record_encoder (int,TYPE_2__*) ; 
 scalar_t__ process_record_keymap (int,TYPE_2__*) ; 
 int /*<<< orphan*/  reset_keyboard () ; 
 int /*<<< orphan*/  rgb_matrix_increase_flags () ; 
 int /*<<< orphan*/  rgb_reset () ; 
 int /*<<< orphan*/  timer_expired (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_read () ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    static uint16_t reset_timer;

#ifndef TAP_DANCE_ENABLE
    if (!process_custom_tap_dance(keycode, record))
        return false;
#endif

    switch (keycode)
    {
        case RGBRST:
#ifdef RGB_ENABLE
            if (record->event.pressed)
                rgb_reset();
#endif
            return false;
        case RESET:
            {
                if (record->event.pressed)
                    reset_timer = timer_read() + 500;
                else if (timer_expired(timer_read(), reset_timer))
                    reset_keyboard();
            }
            return false;
#ifdef RGB_MATRIX_TOG_LAYERS
        case RGB_TOG:
            if (record->event.pressed) {
              rgb_matrix_increase_flags();
            }
            return false;
#endif
  }

  return process_record_encoder(keycode, record) && process_record_keymap(keycode, record);
}