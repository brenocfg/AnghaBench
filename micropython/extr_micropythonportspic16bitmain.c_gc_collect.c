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
typedef  int mp_uint_t ;

/* Variables and functions */
 scalar_t__ MP_STATE_THREAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_collect_end () ; 
 int /*<<< orphan*/  gc_collect_root (void**,int) ; 
 int /*<<< orphan*/  gc_collect_start () ; 
 int /*<<< orphan*/  stack_top ; 

void gc_collect(void) {
    // TODO possibly need to trace registers
    void *dummy;
    gc_collect_start();
    // Node: stack is ascending
    gc_collect_root(&dummy, ((mp_uint_t)&dummy - (mp_uint_t)MP_STATE_THREAD(stack_top)) / sizeof(mp_uint_t));
    gc_collect_end();
}