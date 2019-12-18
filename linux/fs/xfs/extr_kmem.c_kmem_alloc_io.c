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
typedef  int xfs_km_flags_t ;

/* Variables and functions */
 int KM_MAYFAIL ; 
 int PAGE_SIZE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 void* __kmem_vmalloc (size_t,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmem_alloc (size_t,int) ; 
 int /*<<< orphan*/  trace_kmem_alloc_io (size_t,int,int /*<<< orphan*/ ) ; 

void *
kmem_alloc_io(size_t size, int align_mask, xfs_km_flags_t flags)
{
	void	*ptr;

	trace_kmem_alloc_io(size, flags, _RET_IP_);

	if (WARN_ON_ONCE(align_mask >= PAGE_SIZE))
		align_mask = PAGE_SIZE - 1;

	ptr = kmem_alloc(size, flags | KM_MAYFAIL);
	if (ptr) {
		if (!((uintptr_t)ptr & align_mask))
			return ptr;
		kfree(ptr);
	}
	return __kmem_vmalloc(size, flags);
}