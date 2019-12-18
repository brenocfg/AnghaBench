#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mods; } ;

/* Variables and functions */
 int /*<<< orphan*/  FNAV ; 
 scalar_t__ IS_LAYER_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int get_oneshot_mods () ; 
 int /*<<< orphan*/  has_oneshot_mods_timed_out () ; 
 int /*<<< orphan*/  indicate_using_led (int,int) ; 
 TYPE_1__* keyboard_report ; 

void matrix_scan_user(void) {

  /* red led for shift */
  if (keyboard_report->mods & MOD_BIT(KC_LSFT) ||
    ((get_oneshot_mods() & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out())) {
    indicate_using_led(1, true);
  } else {
    indicate_using_led(1, false);
  }

  /* green led for alt */
  if (keyboard_report->mods & MOD_BIT(KC_LALT) ||
    ((get_oneshot_mods() & MOD_BIT(KC_LALT)) && !has_oneshot_mods_timed_out())) {
    indicate_using_led(2, true);
  } else {
    indicate_using_led(2, false);
  }

  /* blue led for function mode */
  if (IS_LAYER_ON(FNAV)) {
    indicate_using_led(3, true);
  } else {
    indicate_using_led(3, false);
  }
}