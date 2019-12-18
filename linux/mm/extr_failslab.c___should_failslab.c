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
struct kmem_cache {int flags; int /*<<< orphan*/  object_size; } ;
typedef  int gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  attr; scalar_t__ cache_filter; scalar_t__ ignore_gfp_reclaim; } ;

/* Variables and functions */
 int SLAB_FAILSLAB ; 
 int __GFP_DIRECT_RECLAIM ; 
 int __GFP_NOFAIL ; 
 TYPE_1__ failslab ; 
 struct kmem_cache* kmem_cache ; 
 int should_fail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

bool __should_failslab(struct kmem_cache *s, gfp_t gfpflags)
{
	/* No fault-injection for bootstrap cache */
	if (unlikely(s == kmem_cache))
		return false;

	if (gfpflags & __GFP_NOFAIL)
		return false;

	if (failslab.ignore_gfp_reclaim &&
			(gfpflags & __GFP_DIRECT_RECLAIM))
		return false;

	if (failslab.cache_filter && !(s->flags & SLAB_FAILSLAB))
		return false;

	return should_fail(&failslab.attr, s->object_size);
}