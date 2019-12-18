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
 int /*<<< orphan*/  KC_C ; 
 int /*<<< orphan*/  KC_V ; 
 int /*<<< orphan*/  LCTL (int /*<<< orphan*/ ) ; 
#define  XC_COPY 129 
#define  XV_PASTE 128 
 int /*<<< orphan*/  tap_code16 (int /*<<< orphan*/ ) ; 

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case XC_COPY:
      if (pressed) {
        tap_code16(LCTL(KC_C));
      }
      break;

    case XV_PASTE:
      if (pressed) {
        tap_code16(LCTL(KC_V));
      }
      break;
  }
}