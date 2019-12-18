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
struct kmem_cache_cpu {int dummy; } ;
struct kmem_cache {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int NUMA_NO_NODE ; 
 void* get_any_partial (struct kmem_cache*,int /*<<< orphan*/ ,struct kmem_cache_cpu*) ; 
 int /*<<< orphan*/  get_node (struct kmem_cache*,int) ; 
 void* get_partial_node (struct kmem_cache*,int /*<<< orphan*/ ,struct kmem_cache_cpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_present_pages (int) ; 
 int node_to_mem_node (int) ; 
 int numa_mem_id () ; 

__attribute__((used)) static void *get_partial(struct kmem_cache *s, gfp_t flags, int node,
		struct kmem_cache_cpu *c)
{
	void *object;
	int searchnode = node;

	if (node == NUMA_NO_NODE)
		searchnode = numa_mem_id();
	else if (!node_present_pages(node))
		searchnode = node_to_mem_node(node);

	object = get_partial_node(s, get_node(s, searchnode), c, flags);
	if (object || node != NUMA_NO_NODE)
		return object;

	return get_any_partial(s, flags, c);
}