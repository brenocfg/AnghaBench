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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  INACTIVE_DELAY ; 
 int /*<<< orphan*/  SLEEP_DELAY ; 
#define  active 131 
#define  boot 130 
 int /*<<< orphan*/  fade_interval ; 
#define  inactive 129 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int) ; 
#define  sleeping 128 
 int state ; 
 int /*<<< orphan*/  timer_elapsed (scalar_t__) ; 
 scalar_t__ timer_read () ; 
 int /*<<< orphan*/  velocikey_decelerate () ; 
 int /*<<< orphan*/  velocikey_match_speed (int,int) ; 

void check_state (void) {
  static uint16_t active_timer;
  if (!active_timer) {active_timer = timer_read();}
  static bool activated, deactivated, slept;
  switch (state) {
  case active:
    if (!activated) {
      if (slept) {rgblight_mode_noeeprom(1);}
      activated = true;
      deactivated = false;
      slept = false;
    }
    fade_interval = velocikey_match_speed(1, 25);
    if (timer_elapsed(active_timer) < INACTIVE_DELAY) {return;}
    active_timer = timer_read();
    state = inactive;
    return;

  case inactive:
    if (!deactivated) {
      deactivated = true;
      activated = false;
      slept = false;
    }
    velocikey_decelerate();
    fade_interval = velocikey_match_speed(1, 25);
    if (timer_elapsed(active_timer) < SLEEP_DELAY) {return;}
    state = sleeping;
    return;

  case sleeping:
    if (!slept) {
      rgblight_mode_noeeprom(5);
      slept = true;
      activated = false;
      deactivated = false;
    }
    return;

  case boot:
    return;
  }
}