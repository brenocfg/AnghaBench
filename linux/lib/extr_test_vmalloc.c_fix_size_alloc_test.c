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
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int test_loop_count ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (int) ; 

__attribute__((used)) static int fix_size_alloc_test(void)
{
	void *ptr;
	int i;

	for (i = 0; i < test_loop_count; i++) {
		ptr = vmalloc(3 * PAGE_SIZE);

		if (!ptr)
			return -1;

		*((__u8 *)ptr) = 0;

		vfree(ptr);
	}

	return 0;
}