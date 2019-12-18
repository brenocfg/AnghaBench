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
struct kmem_cache {int flags; } ;

/* Variables and functions */
 int NR_SLAB_RECLAIMABLE ; 
 int NR_SLAB_UNRECLAIMABLE ; 
 int SLAB_RECLAIM_ACCOUNT ; 

__attribute__((used)) static inline int cache_vmstat_idx(struct kmem_cache *s)
{
	return (s->flags & SLAB_RECLAIM_ACCOUNT) ?
		NR_SLAB_RECLAIMABLE : NR_SLAB_UNRECLAIMABLE;
}