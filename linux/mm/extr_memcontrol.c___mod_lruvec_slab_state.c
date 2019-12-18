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
struct page {int dummy; } ;
struct mem_cgroup {int dummy; } ;
struct lruvec {int dummy; } ;
typedef  int /*<<< orphan*/  pg_data_t ;
typedef  enum node_stat_item { ____Placeholder_node_stat_item } node_stat_item ;

/* Variables and functions */
 int /*<<< orphan*/  __mod_lruvec_state (struct lruvec*,int,int) ; 
 int /*<<< orphan*/  __mod_node_page_state (int /*<<< orphan*/ *,int,int) ; 
 struct lruvec* mem_cgroup_lruvec (int /*<<< orphan*/ *,struct mem_cgroup*) ; 
 struct mem_cgroup* memcg_from_slab_page (struct page*) ; 
 int /*<<< orphan*/ * page_pgdat (struct page*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct mem_cgroup* root_mem_cgroup ; 
 struct page* virt_to_head_page (void*) ; 

void __mod_lruvec_slab_state(void *p, enum node_stat_item idx, int val)
{
	struct page *page = virt_to_head_page(p);
	pg_data_t *pgdat = page_pgdat(page);
	struct mem_cgroup *memcg;
	struct lruvec *lruvec;

	rcu_read_lock();
	memcg = memcg_from_slab_page(page);

	/* Untracked pages have no memcg, no lruvec. Update only the node */
	if (!memcg || memcg == root_mem_cgroup) {
		__mod_node_page_state(pgdat, idx, val);
	} else {
		lruvec = mem_cgroup_lruvec(pgdat, memcg);
		__mod_lruvec_state(lruvec, idx, val);
	}
	rcu_read_unlock();
}