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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ MP_STATE_THREAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_collect_end () ; 
 int /*<<< orphan*/  gc_collect_root (void**,uintptr_t) ; 
 int /*<<< orphan*/  gc_collect_start () ; 
 uintptr_t gc_helper_get_regs_and_sp (uintptr_t*) ; 
 int /*<<< orphan*/  stack_top ; 

void gc_collect(void) {
    gc_collect_start();
    uintptr_t regs[10];
    uintptr_t sp = gc_helper_get_regs_and_sp(regs);
    gc_collect_root((void**)sp, ((uintptr_t)MP_STATE_THREAD(stack_top) - sp) / sizeof(uint32_t));
    gc_collect_end();
}