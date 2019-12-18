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

/* Variables and functions */
#define  DOUBLE 130 
#define  SINGLE_HOLD 129 
#define  TRIPLE 128 
 int /*<<< orphan*/  rgblight_increase_hue_noeeprom () ; 
 int /*<<< orphan*/  rgblight_step_noeeprom () ; 
 int /*<<< orphan*/  rgblight_toggle_noeeprom () ; 
 scalar_t__ tap_dance_active ; 
 int tap_dance_state ; 
 int /*<<< orphan*/  timer ; 
 int timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

void dance_cycle(bool override_timer) {
  if (tap_dance_active)
  {
    if (timer_elapsed(timer) > 100 || override_timer)
    {
      switch (tap_dance_state)
      {
        case SINGLE_HOLD:
        {
          rgblight_increase_hue_noeeprom();
          break;
        }

        case DOUBLE:
        {
          rgblight_step_noeeprom();
          break;
        }

        case TRIPLE:
        {
          rgblight_toggle_noeeprom();
          break;
        }

        default:
          // Not needed
          break;
      }

      timer = timer_read();
    }
  }
}