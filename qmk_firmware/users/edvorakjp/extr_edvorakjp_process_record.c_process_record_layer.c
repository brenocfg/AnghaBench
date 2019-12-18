#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  time; int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  LOWER 129 
#define  RAISE 128 
 int /*<<< orphan*/  TAPPING_TERM ; 
 int /*<<< orphan*/  TIMER_DIFF_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_japanese_mode (int) ; 
 int /*<<< orphan*/  time_on_pressed ; 

bool process_record_layer(uint16_t keycode, keyrecord_t *record) {
#if TAP_DANCE_ENABLE != yes
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        time_on_pressed = record->event.time;
      } else {
        layer_off(_LOWER);

        if (TIMER_DIFF_16(record->event.time, time_on_pressed) < TAPPING_TERM) {
          set_japanese_mode(false);
        }
        time_on_pressed = 0;
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        time_on_pressed = record->event.time;
      } else {
        layer_off(_RAISE);

        if (TIMER_DIFF_16(record->event.time, time_on_pressed) < TAPPING_TERM) {
          set_japanese_mode(true);
        }
        time_on_pressed = 0;
      }
      return false;
  }
#endif
  return true;
}