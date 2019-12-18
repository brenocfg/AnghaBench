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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LEFT ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void surround_type(uint8_t num_of_chars, uint16_t keycode, bool use_shift) {
  if (use_shift) {
    register_code(KC_LSFT);
  }
  for (int i = 0; i < num_of_chars; i++) {
    tap_code(keycode);
  }
  if (use_shift) {
    unregister_code(KC_LSFT);
  }
  for (int i = 0; i < (num_of_chars/2); i++) {
    tap_code(KC_LEFT);
  }
}