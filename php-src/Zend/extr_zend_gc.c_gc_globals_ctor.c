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
typedef  int /*<<< orphan*/  zend_gc_globals ;
typedef  int /*<<< orphan*/  ts_allocate_dtor ;
typedef  int /*<<< orphan*/  ts_allocate_ctor ;

/* Variables and functions */
 int /*<<< orphan*/  gc_globals ; 
 int /*<<< orphan*/  gc_globals_ctor_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_globals_id ; 
 int /*<<< orphan*/  gc_globals_offset ; 
 scalar_t__ root_buffer_dtor ; 
 int /*<<< orphan*/  ts_allocate_fast_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gc_globals_ctor(void)
{
#ifdef ZTS
	ts_allocate_fast_id(&gc_globals_id, &gc_globals_offset, sizeof(zend_gc_globals), (ts_allocate_ctor) gc_globals_ctor_ex, (ts_allocate_dtor) root_buffer_dtor);
#else
	gc_globals_ctor_ex(&gc_globals);
#endif
}