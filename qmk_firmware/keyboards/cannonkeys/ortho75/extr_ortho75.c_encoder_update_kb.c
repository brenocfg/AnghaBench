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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_MEDIA_NEXT_TRACK ; 
 int /*<<< orphan*/  KC_MEDIA_PREV_TRACK ; 
 int /*<<< orphan*/  KC_PGDN ; 
 int /*<<< orphan*/  KC_PGUP ; 
 int /*<<< orphan*/  KC_VOLD ; 
 int /*<<< orphan*/  KC_VOLU ; 
 scalar_t__ MEDIA_KEY_DELAY ; 
 int layer ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void encoder_update_kb(uint8_t index, bool clockwise) {
  uint16_t mapped_code = 0;
  if (index == 0) {
    if (clockwise) {
        switch(layer){
            case 0:
            default:
                mapped_code = KC_VOLU;
                break;
            case 1:
                mapped_code = KC_MEDIA_NEXT_TRACK;
                break;
            case 2:
                mapped_code = KC_PGDN;
                break;
        }
    } else {
        switch(layer){
            case 0:
            default:
                mapped_code = KC_VOLD;
                break;
            case 1:
                mapped_code = KC_MEDIA_PREV_TRACK;
                break;
            case 2:
                mapped_code = KC_PGUP;
                break;
        }
    }
    uint16_t held_keycode_timer = timer_read();
    register_code(mapped_code);
    while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){ /* no-op */ }
    unregister_code(mapped_code);
  }
}