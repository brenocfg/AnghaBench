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

/* Variables and functions */
 size_t PYB_TIMER_OBJ_ALL_NUM ; 
 int /*<<< orphan*/ ** pyb_timer_obj_all ; 

void timer_init0(void) {
    for (uint i = 0; i < PYB_TIMER_OBJ_ALL_NUM; i++) {
        pyb_timer_obj_all[i] = NULL;
    }
}