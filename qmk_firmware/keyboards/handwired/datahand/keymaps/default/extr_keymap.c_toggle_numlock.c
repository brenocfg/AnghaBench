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
 int /*<<< orphan*/  LED_NUM_LOCK ; 
 int /*<<< orphan*/  NAS ; 
 scalar_t__ layer_state_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_led_set (int,int /*<<< orphan*/ ) ; 
 int numlock_enabled ; 
 int /*<<< orphan*/  set_nas (int) ; 

__attribute__((used)) static void toggle_numlock(void) {
  numlock_enabled = !numlock_enabled;
  lock_led_set(numlock_enabled, LED_NUM_LOCK);
  
  if (layer_state_is(NAS)) {
    /* If we're already in NAS, re-set it so that we activate the numlock layer. */
    set_nas(true);
  }
}