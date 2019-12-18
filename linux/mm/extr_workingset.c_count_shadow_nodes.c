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
struct lruvec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DATA (int /*<<< orphan*/ ) ; 
 scalar_t__ NR_LRU_BASE ; 
 int NR_LRU_LISTS ; 
 scalar_t__ NR_SLAB_RECLAIMABLE ; 
 scalar_t__ NR_SLAB_UNRECLAIMABLE ; 
 unsigned long SHRINK_EMPTY ; 
 int XA_CHUNK_SHIFT ; 
 unsigned long list_lru_shrink_count (int /*<<< orphan*/ *,struct shrink_control*) ; 
 scalar_t__ lruvec_page_state_local (struct lruvec*,scalar_t__) ; 
 struct lruvec* mem_cgroup_lruvec (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long node_present_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shadow_nodes ; 

__attribute__((used)) static unsigned long count_shadow_nodes(struct shrinker *shrinker,
					struct shrink_control *sc)
{
	unsigned long max_nodes;
	unsigned long nodes;
	unsigned long pages;

	nodes = list_lru_shrink_count(&shadow_nodes, sc);

	/*
	 * Approximate a reasonable limit for the nodes
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
	 * On 64-bit with 7 xa_nodes per page and 64 slots
	 * each, this will reclaim shadow entries when they consume
	 * ~1.8% of available memory:
	 *
	 * PAGE_SIZE / xa_nodes / node_entries * 8 / PAGE_SIZE
	 */
#ifdef CONFIG_MEMCG
	if (sc->memcg) {
		struct lruvec *lruvec;
		int i;

		lruvec = mem_cgroup_lruvec(NODE_DATA(sc->nid), sc->memcg);
		for (pages = 0, i = 0; i < NR_LRU_LISTS; i++)
			pages += lruvec_page_state_local(lruvec,
							 NR_LRU_BASE + i);
		pages += lruvec_page_state_local(lruvec, NR_SLAB_RECLAIMABLE);
		pages += lruvec_page_state_local(lruvec, NR_SLAB_UNRECLAIMABLE);
	} else
#endif
		pages = node_present_pages(sc->nid);

	max_nodes = pages >> (XA_CHUNK_SHIFT - 3);

	if (!nodes)
		return SHRINK_EMPTY;

	if (nodes <= max_nodes)
		return 0;
	return nodes - max_nodes;
}