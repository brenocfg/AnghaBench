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
struct shrinker {int dummy; } ;
struct shrink_control {int /*<<< orphan*/  nid; scalar_t__ memcg; } ;

/* Variables and functions */
 int /*<<< orphan*/  LRU_ALL_FILE ; 
 int /*<<< orphan*/  NODE_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NR_ACTIVE_FILE ; 
 int /*<<< orphan*/  NR_INACTIVE_FILE ; 
 int RADIX_TREE_MAP_SHIFT ; 
 unsigned long SHRINK_EMPTY ; 
 unsigned long list_lru_shrink_count (int /*<<< orphan*/ *,struct shrink_control*) ; 
 unsigned long mem_cgroup_node_nr_lru_pages (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long node_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shadow_nodes ; 

__attribute__((used)) static unsigned long count_shadow_nodes(struct shrinker *shrinker,
					struct shrink_control *sc)
{
	unsigned long max_nodes;
	unsigned long nodes;
	unsigned long cache;

	nodes = list_lru_shrink_count(&shadow_nodes, sc);

	/*
	 * Approximate a reasonable limit for the radix tree nodes
	 * containing shadow entries. We don't need to keep more
	 * shadow entries than possible pages on the active list,
	 * since refault distances bigger than that are dismissed.
	 *
	 * The size of the active list converges toward 100% of
	 * overall page cache as memory grows, with only a tiny
	 * inactive list. Assume the total cache size for that.
	 *
	 * Nodes might be sparsely populated, with only one shadow
	 * entry in the extreme case. Obviously, we cannot keep one
	 * node for every eligible shadow entry, so compromise on a
	 * worst-case density of 1/8th. Below that, not all eligible
	 * refaults can be detected anymore.
	 *
	 * On 64-bit with 7 radix_tree_nodes per page and 64 slots
	 * each, this will reclaim shadow entries when they consume
	 * ~1.8% of available memory:
	 *
	 * PAGE_SIZE / radix_tree_nodes / node_entries * 8 / PAGE_SIZE
	 */
	if (sc->memcg) {
		cache = mem_cgroup_node_nr_lru_pages(sc->memcg, sc->nid,
						     LRU_ALL_FILE);
	} else {
		cache = node_page_state(NODE_DATA(sc->nid), NR_ACTIVE_FILE) +
			node_page_state(NODE_DATA(sc->nid), NR_INACTIVE_FILE);
	}
	max_nodes = cache >> (RADIX_TREE_MAP_SHIFT - 3);

	if (!nodes)
		return SHRINK_EMPTY;

	if (nodes <= max_nodes)
		return 0;
	return nodes - max_nodes;
}