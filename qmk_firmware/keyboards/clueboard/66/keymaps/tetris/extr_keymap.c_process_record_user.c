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
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  KC_DOWN 131 
#define  KC_LEFT 130 
#define  KC_RIGHT 129 
#define  KC_UP 128 
 int /*<<< orphan*/  tetris_key_presses ; 
 scalar_t__ tetris_keypress ; 
 scalar_t__ tetris_running ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    tetris_key_presses++;
  }

  if (tetris_running && record->event.pressed) {
    tetris_keypress = 0;
    switch (keycode) {
    case KC_UP: tetris_keypress = 1; break;
    case KC_LEFT: tetris_keypress = 2; break;
    case KC_DOWN: tetris_keypress = 3; break;
    case KC_RIGHT: tetris_keypress = 4; break;
    // Make ESC stop tetris (on keyboards other than clueboard)
    // case KC_ESC: tetris_running = 0; return false;
    }
    if (tetris_keypress != 0) {
      return false;
    }
  }

  return true;
}