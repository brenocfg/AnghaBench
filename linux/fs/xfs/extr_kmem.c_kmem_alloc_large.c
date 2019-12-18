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
 int /*<<< orphan*/  _RET_IP_ ; 
 void* __kmem_vmalloc (size_t,int) ; 
 void* kmem_alloc (size_t,int) ; 
 int /*<<< orphan*/  trace_kmem_alloc_large (size_t,int,int /*<<< orphan*/ ) ; 

void *
kmem_alloc_large(size_t size, xfs_km_flags_t flags)
{
	void	*ptr;

	trace_kmem_alloc_large(size, flags, _RET_IP_);

	ptr = kmem_alloc(size, flags | KM_MAYFAIL);
	if (ptr)
		return ptr;
	return __kmem_vmalloc(size, flags);
}