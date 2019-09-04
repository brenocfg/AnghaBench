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
typedef  size_t uint ;
typedef  int /*<<< orphan*/  pyb_timer_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 size_t PYB_TIMER_OBJ_ALL_NUM ; 
 int /*<<< orphan*/  pyb_timer_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pyb_timer_obj_all ; 

void timer_deinit(void) {
    for (uint i = 0; i < PYB_TIMER_OBJ_ALL_NUM; i++) {
        pyb_timer_obj_t *tim = MP_STATE_PORT(pyb_timer_obj_all)[i];
        if (tim != NULL) {
            pyb_timer_deinit(MP_OBJ_FROM_PTR(tim));
        }
    }
}