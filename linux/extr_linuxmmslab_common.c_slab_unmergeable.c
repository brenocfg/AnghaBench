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
struct kmem_cache {int flags; scalar_t__ refcount; scalar_t__ usersize; scalar_t__ ctor; } ;

/* Variables and functions */
 int SLAB_NEVER_MERGE ; 
 int /*<<< orphan*/  is_root_cache (struct kmem_cache*) ; 
 scalar_t__ slab_nomerge ; 

int slab_unmergeable(struct kmem_cache *s)
{
	if (slab_nomerge || (s->flags & SLAB_NEVER_MERGE))
		return 1;

	if (!is_root_cache(s))
		return 1;

	if (s->ctor)
		return 1;

	if (s->usersize)
		return 1;

	/*
	 * We may have set a slab to be unmergeable during bootstrap.
	 */
	if (s->refcount < 0)
		return 1;

	return 0;
}