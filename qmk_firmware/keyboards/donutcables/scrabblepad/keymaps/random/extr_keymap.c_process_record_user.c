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
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LSHIFT ; 
#define  RND_KEY 128 
 int /*<<< orphan*/  keystroke ; 
 int rand () ; 
 int /*<<< orphan*/  random_keycode () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int shift_pressed ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case RND_KEY:
      if (record->event.pressed) {
        keystroke = random_keycode();
        if (rand() % 2 > 0) {
          shift_pressed = 1;
          register_code(KC_LSHIFT);
        }
        register_code(keystroke);
      } else {
        if (shift_pressed > 0) {
          unregister_code(KC_LSHIFT);
        }
        unregister_code(keystroke);
      }

      return false;

    default:
        return true;
  }

  return true;
}