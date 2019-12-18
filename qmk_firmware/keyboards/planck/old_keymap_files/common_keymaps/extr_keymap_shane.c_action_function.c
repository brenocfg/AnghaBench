#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  count; } ;
struct TYPE_6__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_7__ {TYPE_1__ tap; TYPE_2__ event; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_SPC ; 
#define  SPACE_FN 128 
 int /*<<< orphan*/  add_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int) ; 
 unsigned long layer_state ; 
 int /*<<< orphan*/  send_keyboard_report () ; 

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch (id) {
  case SPACE_FN:
    if (record->event.pressed) {
      // Change the keyboard maps.
      // Whatever even layer's are on, turn on the odd one's too.
      for (uint8_t i = 0; i < 9; i += 2) {
        if (layer_state & (1UL << i))
          layer_on(i + 1);
      }
      layer_on(1);
    } else {
      // turn off all the even layers.
      for (uint8_t i = 0; i < 9; i += 2)
        layer_off(i + 1);

      if (record->tap.count != 0) {
        // Space was tapped rather than used like a modifier.
        // So send a space up and down event.
        add_key(KC_SPC);
        send_keyboard_report();
        del_key(KC_SPC);
        send_keyboard_report();
      }
    }
    break;
  }
}