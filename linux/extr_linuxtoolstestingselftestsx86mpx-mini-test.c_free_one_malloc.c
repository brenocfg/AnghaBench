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
struct TYPE_2__ {int /*<<< orphan*/ * ptr; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int alignment ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dprintf4 (char*,unsigned long,unsigned long,...) ; 
 TYPE_1__* mallocs ; 
 int /*<<< orphan*/  mpx_mini_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void free_one_malloc(int index)
{
	unsigned long free_ptr;
	unsigned long mask;

	if (!mallocs[index].ptr)
		return;

	mpx_mini_free(mallocs[index].ptr, mallocs[index].size);
	dprintf4("freed[%d]:  %p\n", index, mallocs[index].ptr);

	free_ptr = (unsigned long)mallocs[index].ptr;
	mask = alignment-1;
	dprintf4("lowerbits: %lx / %lx mask: %lx\n", free_ptr,
			(free_ptr & mask), mask);
	assert((free_ptr & mask) == 0);

	mallocs[index].ptr = NULL;
}