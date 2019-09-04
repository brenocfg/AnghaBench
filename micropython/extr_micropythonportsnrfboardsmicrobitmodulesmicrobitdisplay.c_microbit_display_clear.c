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
 int /*<<< orphan*/  ASYNC_MODE_CLEAR ; 
 scalar_t__ MILLISECONDS_PER_MACRO_TICK ; 
 scalar_t__ async_delay ; 
 int /*<<< orphan*/  async_mode ; 
 scalar_t__ async_tick ; 
 int /*<<< orphan*/  wait_for_event () ; 
 int wakeup_event ; 

void microbit_display_clear(void) {
    // Reset repeat state, cancel animation and clear screen.
    wakeup_event = false;
    async_mode = ASYNC_MODE_CLEAR;
    async_tick = async_delay - MILLISECONDS_PER_MACRO_TICK;
    wait_for_event();
}