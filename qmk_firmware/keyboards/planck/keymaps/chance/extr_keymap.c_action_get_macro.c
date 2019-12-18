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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  macro_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_DEL ; 
 int /*<<< orphan*/  KC_ESC ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_RCTL ; 
 int /*<<< orphan*/  KC_RSFT ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
    if (record->event.pressed) {
      register_code(KC_RSFT);
      register_code(KC_RCTL);
      register_code(KC_ESC);
    }
    else{
      clear_keyboard();
    }
    break;
    case 1:
    if (record->event.pressed) {
      register_code(KC_LCTL);
      register_code(KC_LALT);
      register_code(KC_DEL);
    }
    else{
      clear_keyboard();
    }
    break;
  }
  return MACRO_NONE;
}