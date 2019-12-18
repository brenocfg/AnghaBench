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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LBRC ; 
 int /*<<< orphan*/  KC_RBRC ; 
 int /*<<< orphan*/  LGUI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code16 (int /*<<< orphan*/ ) ; 

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) {
      // Tab right
      tap_code16(LSFT(LGUI(KC_RBRC)));
    } else {
      // Tab left
      tap_code16(LSFT(LGUI(KC_LBRC)));
    }
  }
  else if (index == 1) {
    if (clockwise) {
      // History forward
      tap_code16(LGUI(KC_RBRC));
    } else {
      // History back
      tap_code16(LGUI(KC_LBRC));
    }
  }
}