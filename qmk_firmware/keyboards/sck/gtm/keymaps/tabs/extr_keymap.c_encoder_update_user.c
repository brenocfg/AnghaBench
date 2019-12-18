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
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KC_T ; 
 int /*<<< orphan*/  KC_W ; 
 int /*<<< orphan*/  tap_code16 (int /*<<< orphan*/ ) ; 

void encoder_update_user(int8_t index, bool clockwise) {
    if (clockwise) {
      tap_code16(C(KC_T));
    } else {
      tap_code16(C(KC_W));
    }
}