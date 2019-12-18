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
typedef  size_t uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ANSWERS ; 
#define  KC_A 128 
 size_t NO_BREAK ; 
 int NUM_ANSWERS ; 
 int RAND_MAX ; 
 size_t UNCERTAIN_BREAK ; 
 int /*<<< orphan*/  lastTime ; 
 size_t rand () ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_setrgb_green () ; 
 int /*<<< orphan*/  rgblight_setrgb_red () ; 
 int /*<<< orphan*/  rgblight_setrgb_yellow () ; 
 int /*<<< orphan*/  send_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read32 () ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_A:
    if (record->event.pressed) {
      uint8_t num = rand() / (RAND_MAX / NUM_ANSWERS + 1);
      rgblight_mode(1);
      if (num < UNCERTAIN_BREAK) {
        rgblight_setrgb_green();
      } else if (num < NO_BREAK) {
        rgblight_setrgb_yellow();
      } else {
        rgblight_setrgb_red();
      }
      send_string(ANSWERS[num]);
      lastTime = timer_read32();
      return false;
    }
  }
  return true;
}