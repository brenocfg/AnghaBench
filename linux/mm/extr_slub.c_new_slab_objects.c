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
struct page {int /*<<< orphan*/ * freelist; } ;
struct kmem_cache_cpu {struct page* page; } ;
struct kmem_cache {int /*<<< orphan*/  cpu_slab; scalar_t__ ctor; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_SLAB ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  flush_slab (struct kmem_cache*,struct kmem_cache_cpu*) ; 
 void* get_partial (struct kmem_cache*,int,int,struct kmem_cache_cpu*) ; 
 struct page* new_slab (struct kmem_cache*,int,int) ; 
 struct kmem_cache_cpu* raw_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat (struct kmem_cache*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *new_slab_objects(struct kmem_cache *s, gfp_t flags,
			int node, struct kmem_cache_cpu **pc)
{
	void *freelist;
	struct kmem_cache_cpu *c = *pc;
	struct page *page;

	WARN_ON_ONCE(s->ctor && (flags & __GFP_ZERO));

	freelist = get_partial(s, flags, node, c);

	if (freelist)
		return freelist;

	page = new_slab(s, flags, node);
	if (page) {
		c = raw_cpu_ptr(s->cpu_slab);
		if (c->page)
			flush_slab(s, c);

		/*
		 * No other reference to the page yet so we can
		 * muck around with it freely without cmpxchg
		 */
		freelist = page->freelist;
		page->freelist = NULL;

		stat(s, ALLOC_SLAB);
		c->page = page;
		*pc = c;
	}

	return freelist;
}