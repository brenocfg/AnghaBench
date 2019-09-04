#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int gc_protected; scalar_t__ collected; scalar_t__ gc_runs; scalar_t__ num_roots; void* buf_size; void* gc_threshold; void* first_unused; void* unused; int /*<<< orphan*/ * buf; scalar_t__ gc_full; scalar_t__ gc_active; scalar_t__ gc_enabled; } ;
typedef  TYPE_1__ zend_gc_globals ;

/* Variables and functions */
 void* GC_INVALID ; 

__attribute__((used)) static void gc_globals_ctor_ex(zend_gc_globals *gc_globals)
{
	gc_globals->gc_enabled = 0;
	gc_globals->gc_active = 0;
	gc_globals->gc_protected = 1;
	gc_globals->gc_full = 0;

	gc_globals->buf = NULL;
	gc_globals->unused = GC_INVALID;
	gc_globals->first_unused = GC_INVALID;
	gc_globals->gc_threshold = GC_INVALID;
	gc_globals->buf_size = GC_INVALID;
	gc_globals->num_roots = 0;

	gc_globals->gc_runs = 0;
	gc_globals->collected = 0;

#if GC_BENCH
	gc_globals->root_buf_length = 0;
	gc_globals->root_buf_peak = 0;
	gc_globals->zval_possible_root = 0;
	gc_globals->zval_buffered = 0;
	gc_globals->zval_remove_from_buffer = 0;
	gc_globals->zval_marked_grey = 0;
#endif
}