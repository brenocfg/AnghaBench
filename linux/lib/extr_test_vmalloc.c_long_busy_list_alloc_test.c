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
typedef  int __u8 ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int test_loop_count ; 
 int /*<<< orphan*/  vfree (void**) ; 
 void* vmalloc (int) ; 

__attribute__((used)) static int long_busy_list_alloc_test(void)
{
	void *ptr_1, *ptr_2;
	void **ptr;
	int rv = -1;
	int i;

	ptr = vmalloc(sizeof(void *) * 15000);
	if (!ptr)
		return rv;

	for (i = 0; i < 15000; i++)
		ptr[i] = vmalloc(1 * PAGE_SIZE);

	for (i = 0; i < test_loop_count; i++) {
		ptr_1 = vmalloc(100 * PAGE_SIZE);
		if (!ptr_1)
			goto leave;

		ptr_2 = vmalloc(1 * PAGE_SIZE);
		if (!ptr_2) {
			vfree(ptr_1);
			goto leave;
		}

		*((__u8 *)ptr_1) = 0;
		*((__u8 *)ptr_2) = 1;

		vfree(ptr_1);
		vfree(ptr_2);
	}

	/*  Success */
	rv = 0;

leave:
	for (i = 0; i < 15000; i++)
		vfree(ptr[i]);

	vfree(ptr);
	return rv;
}