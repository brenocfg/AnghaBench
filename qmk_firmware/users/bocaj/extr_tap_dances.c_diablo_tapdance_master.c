#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_4__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/ * diablo_key_time ; 
 int /*<<< orphan*/ * diablo_times ; 
 int /*<<< orphan*/  reset_tap_dance (TYPE_1__*) ; 

void diablo_tapdance_master(qk_tap_dance_state_t *state, void *user_data, uint8_t diablo_key) {
  if (state->count >= 7) {
    diablo_key_time[diablo_key] = diablo_times[0];
    reset_tap_dance(state);
  }  else {
    diablo_key_time[diablo_key] = diablo_times[state->count - 1];
  }
}