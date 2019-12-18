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
struct kmem_cache {int size; int /*<<< orphan*/  flags; int /*<<< orphan*/  (* ctor ) (void*) ;int /*<<< orphan*/  object_size; int /*<<< orphan*/  align; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int SLOB_UNIT ; 
 int SLOB_UNITS (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  fs_reclaim_acquire (int) ; 
 int /*<<< orphan*/  fs_reclaim_release (int) ; 
 int get_order (int) ; 
 int gfp_allowed_mask ; 
 int /*<<< orphan*/  kmemleak_alloc_recursive (void*,int,int,int /*<<< orphan*/ ,int) ; 
 void* slob_alloc (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* slob_new_pages (int,int,int) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  trace_kmem_cache_alloc_node (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void *slob_alloc_node(struct kmem_cache *c, gfp_t flags, int node)
{
	void *b;

	flags &= gfp_allowed_mask;

	fs_reclaim_acquire(flags);
	fs_reclaim_release(flags);

	if (c->size < PAGE_SIZE) {
		b = slob_alloc(c->size, flags, c->align, node, 0);
		trace_kmem_cache_alloc_node(_RET_IP_, b, c->object_size,
					    SLOB_UNITS(c->size) * SLOB_UNIT,
					    flags, node);
	} else {
		b = slob_new_pages(flags, get_order(c->size), node);
		trace_kmem_cache_alloc_node(_RET_IP_, b, c->object_size,
					    PAGE_SIZE << get_order(c->size),
					    flags, node);
	}

	if (b && c->ctor) {
		WARN_ON_ONCE(flags & __GFP_ZERO);
		c->ctor(b);
	}

	kmemleak_alloc_recursive(b, c->size, 1, c->flags, flags);
	return b;
}