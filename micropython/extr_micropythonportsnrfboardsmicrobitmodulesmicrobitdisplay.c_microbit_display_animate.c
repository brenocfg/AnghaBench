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
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  mp_int_t ;
typedef  int /*<<< orphan*/  microbit_display_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_MODE_ANIMATION ; 
 int /*<<< orphan*/ ** MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int async_clear ; 
 int /*<<< orphan*/  async_data ; 
 int /*<<< orphan*/  async_delay ; 
 int /*<<< orphan*/ * async_iterator ; 
 int /*<<< orphan*/  async_mode ; 
 scalar_t__ async_tick ; 
 int /*<<< orphan*/  draw_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mp_getiter (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_iternext_allow_raise (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_event () ; 
 int wakeup_event ; 

void microbit_display_animate(microbit_display_obj_t *self, mp_obj_t iterable, mp_int_t delay, bool clear, bool wait) {
    // Reset the repeat state.
    MP_STATE_PORT(async_data)[0] = NULL;
    MP_STATE_PORT(async_data)[1] = NULL;
    async_iterator = mp_getiter(iterable, NULL);
    async_delay = delay;
    async_clear = clear;
    MP_STATE_PORT(async_data)[0] = self; // so it doesn't get GC'd
    MP_STATE_PORT(async_data)[1] = async_iterator;
    wakeup_event = false;
    mp_obj_t obj = mp_iternext_allow_raise(async_iterator);
    draw_object(obj);
    async_tick = 0;
    async_mode = ASYNC_MODE_ANIMATION;
    if (wait) {
        wait_for_event();
    }
}