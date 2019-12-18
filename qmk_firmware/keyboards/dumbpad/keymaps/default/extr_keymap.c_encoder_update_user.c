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

/* Variables and functions */
 int /*<<< orphan*/  KC_EQL ; 
 int /*<<< orphan*/  KC_MINS ; 
 int /*<<< orphan*/  KC_MS_L ; 
 int /*<<< orphan*/  KC_MS_R ; 
#define  _BASE 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 

void encoder_update_user(uint8_t index, bool clockwise) {
  /*  Custom encoder control - handles CW/CCW turning of encoder
   *  Default behavior:
   *    main layer:
   *       CW: move mouse right
   *      CCW: move mouse left
   *    other layers:
   *       CW: = (equals/plus - increase slider in Adobe products)
   *      CCW: - (minus/underscore - decrease slider in adobe products)
   */
  if (index == 0) {
    switch (biton32(layer_state)) {
      case _BASE:
        // main layer - move mouse right (CW) and left (CCW)
        if (clockwise) {
          tap_code(KC_MS_R);
        } else {
          tap_code(KC_MS_L);
        }
        break;

      default:
        // other layers - =/+ (quals/plus) (CW) and -/_ (minus/underscore) (CCW)
        if (clockwise) {
          tap_code(KC_EQL);
        } else {
          tap_code(KC_MINS);
        }
        break;
    }
  }
}