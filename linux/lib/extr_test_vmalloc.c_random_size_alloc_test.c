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
typedef  int /*<<< orphan*/  i ;
typedef  int __u8 ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  get_random_bytes (unsigned int*,int) ; 
 int test_loop_count ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (unsigned int) ; 

__attribute__((used)) static int random_size_alloc_test(void)
{
	unsigned int n;
	void *p;
	int i;

	for (i = 0; i < test_loop_count; i++) {
		get_random_bytes(&n, sizeof(i));
		n = (n % 100) + 1;

		p = vmalloc(n * PAGE_SIZE);

		if (!p)
			return -1;

		*((__u8 *)p) = 1;
		vfree(p);
	}

	return 0;
}