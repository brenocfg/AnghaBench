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
typedef  int uint32_t ;
typedef  int volatile mp_uint_t ;

/* Variables and functions */
 scalar_t__ MP_STATE_THREAD (int /*<<< orphan*/ ) ; 
 int XCHAL_NUM_AREGS ; 
 int /*<<< orphan*/  gc_collect_root (void**,int volatile) ; 
 int /*<<< orphan*/  get_sp () ; 
 int /*<<< orphan*/  mp_thread_gc_others () ; 
 int /*<<< orphan*/  stack_top ; 

__attribute__((used)) static void gc_collect_inner(int level) {
    if (level < XCHAL_NUM_AREGS / 8) {
        gc_collect_inner(level + 1);
        if (level != 0) {
            return;
        }
    }

    if (level == XCHAL_NUM_AREGS / 8) {
        // get the sp
        volatile uint32_t sp = (uint32_t)get_sp();
        gc_collect_root((void**)sp, ((mp_uint_t)MP_STATE_THREAD(stack_top) - sp) / sizeof(uint32_t));
        return;
    }

    // trace root pointers from any threads
    #if MICROPY_PY_THREAD
    mp_thread_gc_others();
    #endif
}