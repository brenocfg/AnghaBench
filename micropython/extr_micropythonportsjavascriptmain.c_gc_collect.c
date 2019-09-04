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
typedef  int /*<<< orphan*/  jmp_buf ;

/* Variables and functions */
 int /*<<< orphan*/  gc_collect_end () ; 
 int /*<<< orphan*/  gc_collect_root (void*,int) ; 
 int /*<<< orphan*/  gc_collect_start () ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 scalar_t__ stack_top ; 

void gc_collect(void) {
    // WARNING: This gc_collect implementation doesn't try to get root
    // pointers from CPU registers, and thus may function incorrectly.
    jmp_buf dummy;
    if (setjmp(dummy) == 0) {
        longjmp(dummy, 1);
    }
    gc_collect_start();
    gc_collect_root((void*)stack_top, ((mp_uint_t)(void*)(&dummy + 1) - (mp_uint_t)stack_top) / sizeof(mp_uint_t));
    gc_collect_end();
}