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
typedef  char* MP_STATE_THREAD ;

/* Variables and functions */

void mp_stack_ctrl_init(void) {
    volatile int stack_dummy;
    MP_STATE_THREAD(stack_top) = (char*)&stack_dummy;
}