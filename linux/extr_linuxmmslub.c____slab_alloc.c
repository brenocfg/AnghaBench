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
struct page {int /*<<< orphan*/  frozen; } ;
struct kmem_cache_cpu {struct page* page; int /*<<< orphan*/  tid; void* freelist; } ;
struct kmem_cache {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_NODE_MISMATCH ; 
 int /*<<< orphan*/  ALLOC_REFILL ; 
 int /*<<< orphan*/  CPU_PARTIAL_ALLOC ; 
 int /*<<< orphan*/  DEACTIVATE_BYPASS ; 
 int NUMA_NO_NODE ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  alloc_debug_processing (struct kmem_cache*,struct page*,void*,unsigned long) ; 
 int /*<<< orphan*/  deactivate_slab (struct kmem_cache*,struct page*,void*,struct kmem_cache_cpu*) ; 
 void* get_freelist (struct kmem_cache*,struct page*) ; 
 void* get_freepointer (struct kmem_cache*,void*) ; 
 scalar_t__ kmem_cache_debug (struct kmem_cache*) ; 
 scalar_t__ likely (int) ; 
 void* new_slab_objects (struct kmem_cache*,int /*<<< orphan*/ ,int,struct kmem_cache_cpu**) ; 
 int /*<<< orphan*/  next_tid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_match (struct page*,int) ; 
 int /*<<< orphan*/  node_present_pages (int) ; 
 int node_to_mem_node (int) ; 
 scalar_t__ pfmemalloc_match (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slab_out_of_memory (struct kmem_cache*,int /*<<< orphan*/ ,int) ; 
 struct page* slub_percpu_partial (struct kmem_cache_cpu*) ; 
 int /*<<< orphan*/  slub_set_percpu_partial (struct kmem_cache_cpu*,struct page*) ; 
 int /*<<< orphan*/  stat (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void *___slab_alloc(struct kmem_cache *s, gfp_t gfpflags, int node,
			  unsigned long addr, struct kmem_cache_cpu *c)
{
	void *freelist;
	struct page *page;

	page = c->page;
	if (!page)
		goto new_slab;
redo:

	if (unlikely(!node_match(page, node))) {
		int searchnode = node;

		if (node != NUMA_NO_NODE && !node_present_pages(node))
			searchnode = node_to_mem_node(node);

		if (unlikely(!node_match(page, searchnode))) {
			stat(s, ALLOC_NODE_MISMATCH);
			deactivate_slab(s, page, c->freelist, c);
			goto new_slab;
		}
	}

	/*
	 * By rights, we should be searching for a slab page that was
	 * PFMEMALLOC but right now, we are losing the pfmemalloc
	 * information when the page leaves the per-cpu allocator
	 */
	if (unlikely(!pfmemalloc_match(page, gfpflags))) {
		deactivate_slab(s, page, c->freelist, c);
		goto new_slab;
	}

	/* must check again c->freelist in case of cpu migration or IRQ */
	freelist = c->freelist;
	if (freelist)
		goto load_freelist;

	freelist = get_freelist(s, page);

	if (!freelist) {
		c->page = NULL;
		stat(s, DEACTIVATE_BYPASS);
		goto new_slab;
	}

	stat(s, ALLOC_REFILL);

load_freelist:
	/*
	 * freelist is pointing to the list of objects to be used.
	 * page is pointing to the page from which the objects are obtained.
	 * That page must be frozen for per cpu allocations to work.
	 */
	VM_BUG_ON(!c->page->frozen);
	c->freelist = get_freepointer(s, freelist);
	c->tid = next_tid(c->tid);
	return freelist;

new_slab:

	if (slub_percpu_partial(c)) {
		page = c->page = slub_percpu_partial(c);
		slub_set_percpu_partial(c, page);
		stat(s, CPU_PARTIAL_ALLOC);
		goto redo;
	}

	freelist = new_slab_objects(s, gfpflags, node, &c);

	if (unlikely(!freelist)) {
		slab_out_of_memory(s, gfpflags, node);
		return NULL;
	}

	page = c->page;
	if (likely(!kmem_cache_debug(s) && pfmemalloc_match(page, gfpflags)))
		goto load_freelist;

	/* Only entered in the debug case */
	if (kmem_cache_debug(s) &&
			!alloc_debug_processing(s, page, freelist, addr))
		goto new_slab;	/* Slab failed checks. Next slab needed */

	deactivate_slab(s, page, get_freepointer(s, freelist), c);
	return freelist;
}