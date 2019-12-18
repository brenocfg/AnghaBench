#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* (* realloc ) (void*,int) ;} ;

/* Variables and functions */
 TYPE_1__ alloc ; 
 int /*<<< orphan*/  bcrash (char*,unsigned long) ; 
 int /*<<< orphan*/  num_allocs ; 
 int /*<<< orphan*/  os_atomic_inc_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_breakpoint () ; 
 void* stub1 (void*,size_t) ; 
 void* stub2 (void*,int) ; 

void *brealloc(void *ptr, size_t size)
{
	if (!ptr)
		os_atomic_inc_long(&num_allocs);

	ptr = alloc.realloc(ptr, size);
	if (!ptr && !size)
		ptr = alloc.realloc(ptr, 1);
	if (!ptr) {
		os_breakpoint();
		bcrash("Out of memory while trying to allocate %lu bytes",
		       (unsigned long)size);
	}

	return ptr;
}