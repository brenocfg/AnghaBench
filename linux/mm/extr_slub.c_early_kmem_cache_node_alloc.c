#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct page {int inuse; int /*<<< orphan*/  objects; scalar_t__ frozen; struct kmem_cache_node* freelist; } ;
struct kmem_cache_node {int dummy; } ;
struct TYPE_8__ {int size; struct kmem_cache_node** node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DEACTIVATE_TO_HEAD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  SLUB_RED_ACTIVE ; 
 int /*<<< orphan*/  __add_partial (struct kmem_cache_node*,struct page*,int /*<<< orphan*/ ) ; 
 struct kmem_cache_node* get_freepointer (TYPE_1__*,struct kmem_cache_node*) ; 
 int /*<<< orphan*/  inc_slabs_node (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_kmem_cache_node (struct kmem_cache_node*) ; 
 int /*<<< orphan*/  init_object (TYPE_1__*,struct kmem_cache_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_tracking (TYPE_1__*,struct kmem_cache_node*) ; 
 struct kmem_cache_node* kasan_kmalloc (TYPE_1__*,struct kmem_cache_node*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* kmem_cache_node ; 
 struct page* new_slab (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int page_to_nid (struct page*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static void early_kmem_cache_node_alloc(int node)
{
	struct page *page;
	struct kmem_cache_node *n;

	BUG_ON(kmem_cache_node->size < sizeof(struct kmem_cache_node));

	page = new_slab(kmem_cache_node, GFP_NOWAIT, node);

	BUG_ON(!page);
	if (page_to_nid(page) != node) {
		pr_err("SLUB: Unable to allocate memory from node %d\n", node);
		pr_err("SLUB: Allocating a useless per node structure in order to be able to continue\n");
	}

	n = page->freelist;
	BUG_ON(!n);
#ifdef CONFIG_SLUB_DEBUG
	init_object(kmem_cache_node, n, SLUB_RED_ACTIVE);
	init_tracking(kmem_cache_node, n);
#endif
	n = kasan_kmalloc(kmem_cache_node, n, sizeof(struct kmem_cache_node),
		      GFP_KERNEL);
	page->freelist = get_freepointer(kmem_cache_node, n);
	page->inuse = 1;
	page->frozen = 0;
	kmem_cache_node->node[node] = n;
	init_kmem_cache_node(n);
	inc_slabs_node(kmem_cache_node, node, page->objects);

	/*
	 * No locks need to be taken here as it has just been
	 * initialized and there is no concurrent access.
	 */
	__add_partial(n, page, DEACTIVATE_TO_HEAD);
}