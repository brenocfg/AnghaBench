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
 int KM_ZERO ; 
 void* kmem_alloc (size_t,int) ; 

__attribute__((used)) static inline void *
kmem_zalloc(size_t size, xfs_km_flags_t flags)
{
	return kmem_alloc(size, flags | KM_ZERO);
}