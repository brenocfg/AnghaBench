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
typedef  int ptrdiff_t ;

/* Variables and functions */
 int PTRDIFF_MAX ; 
 int SIZE_MAX ; 
 int WORK_AROUND_QTBUG_53071 ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* erealloc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_exhausted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_product (int,size_t) ; 

__attribute__((used)) static void *
growalloc(void *ptr, size_t itemsize, ptrdiff_t nitems, ptrdiff_t *nitems_alloc)
{
	if (nitems < *nitems_alloc)
		return ptr;
	else
	{
		ptrdiff_t	nitems_max = PTRDIFF_MAX - WORK_AROUND_QTBUG_53071;
		ptrdiff_t	amax = nitems_max < SIZE_MAX ? nitems_max : SIZE_MAX;

		if ((amax - 1) / 3 * 2 < *nitems_alloc)
			memory_exhausted(_("integer overflow"));
		*nitems_alloc += (*nitems_alloc >> 1) + 1;
		return erealloc(ptr, size_product(*nitems_alloc, itemsize));
	}
}