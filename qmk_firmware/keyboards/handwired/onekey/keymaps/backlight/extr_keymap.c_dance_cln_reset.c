#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  breathing_pulse () ; 
 int /*<<< orphan*/  breathing_toggle () ; 

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      // single tap - step through backlight
      backlight_step();
      break;
#ifdef BACKLIGHT_BREATHING
    case 2:
      // double tap - toggle breathing
      breathing_toggle();
      break;
    case 3:
      //tripple tap - do some pulse stuff
      breathing_pulse();
      break;
#endif
    default:
      // more - nothing
      break;
  }
}