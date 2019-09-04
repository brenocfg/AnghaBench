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
typedef  int gfp_t ;

/* Variables and functions */
 size_t PAGE_ALLOC_COSTLY_ORDER ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 size_t PAGE_SIZE ; 
 int __GFP_NOWARN ; 
 void* __vmalloc (size_t,int,int /*<<< orphan*/ ) ; 
 void* kmalloc (size_t,int) ; 

void *ceph_kvmalloc(size_t size, gfp_t flags)
{
	if (size <= (PAGE_SIZE << PAGE_ALLOC_COSTLY_ORDER)) {
		void *ptr = kmalloc(size, flags | __GFP_NOWARN);
		if (ptr)
			return ptr;
	}

	return __vmalloc(size, flags, PAGE_KERNEL);
}