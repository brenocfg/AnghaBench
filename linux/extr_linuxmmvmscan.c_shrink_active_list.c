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
struct zone_reclaim_stat {unsigned long* recent_scanned; unsigned int* recent_rotated; } ;
struct scan_control {int /*<<< orphan*/  priority; int /*<<< orphan*/  target_mem_cgroup; int /*<<< orphan*/  may_unmap; } ;
struct pglist_data {int /*<<< orphan*/  node_id; int /*<<< orphan*/  lru_lock; } ;
struct page {int /*<<< orphan*/  lru; } ;
struct lruvec {struct zone_reclaim_stat reclaim_stat; } ;
typedef  int /*<<< orphan*/  isolate_mode_t ;
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageActive (struct page*) ; 
 int /*<<< orphan*/  ISOLATE_UNMAPPED ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int LRU_ACTIVE ; 
 scalar_t__ NR_ISOLATED_ANON ; 
 int /*<<< orphan*/  PGREFILL ; 
 unsigned long VM_EXEC ; 
 int /*<<< orphan*/  __count_vm_events (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  __mod_node_page_state (struct pglist_data*,scalar_t__,unsigned long) ; 
 int buffer_heads_over_limit ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  count_memcg_events (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  free_unref_page_list (int /*<<< orphan*/ *) ; 
 scalar_t__ hpage_nr_pages (struct page*) ; 
 int is_file_lru (int) ; 
 unsigned long isolate_lru_pages (unsigned long,struct lruvec*,int /*<<< orphan*/ *,unsigned long*,struct scan_control*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  l_active ; 
 int /*<<< orphan*/  l_hold ; 
 int /*<<< orphan*/  l_inactive ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 struct page* lru_to_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lruvec_memcg (struct lruvec*) ; 
 struct pglist_data* lruvec_pgdat (struct lruvec*) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_list (int /*<<< orphan*/ *) ; 
 unsigned int move_active_pages_to_lru (struct lruvec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  page_evictable (struct page*) ; 
 scalar_t__ page_has_private (struct page*) ; 
 scalar_t__ page_is_file_cache (struct page*) ; 
 scalar_t__ page_referenced (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  putback_lru_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mm_vmscan_lru_shrink_active (int /*<<< orphan*/ ,unsigned long,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  try_to_release_page (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ trylock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void shrink_active_list(unsigned long nr_to_scan,
			       struct lruvec *lruvec,
			       struct scan_control *sc,
			       enum lru_list lru)
{
	unsigned long nr_taken;
	unsigned long nr_scanned;
	unsigned long vm_flags;
	LIST_HEAD(l_hold);	/* The pages which were snipped off */
	LIST_HEAD(l_active);
	LIST_HEAD(l_inactive);
	struct page *page;
	struct zone_reclaim_stat *reclaim_stat = &lruvec->reclaim_stat;
	unsigned nr_deactivate, nr_activate;
	unsigned nr_rotated = 0;
	isolate_mode_t isolate_mode = 0;
	int file = is_file_lru(lru);
	struct pglist_data *pgdat = lruvec_pgdat(lruvec);

	lru_add_drain();

	if (!sc->may_unmap)
		isolate_mode |= ISOLATE_UNMAPPED;

	spin_lock_irq(&pgdat->lru_lock);

	nr_taken = isolate_lru_pages(nr_to_scan, lruvec, &l_hold,
				     &nr_scanned, sc, isolate_mode, lru);

	__mod_node_page_state(pgdat, NR_ISOLATED_ANON + file, nr_taken);
	reclaim_stat->recent_scanned[file] += nr_taken;

	__count_vm_events(PGREFILL, nr_scanned);
	count_memcg_events(lruvec_memcg(lruvec), PGREFILL, nr_scanned);

	spin_unlock_irq(&pgdat->lru_lock);

	while (!list_empty(&l_hold)) {
		cond_resched();
		page = lru_to_page(&l_hold);
		list_del(&page->lru);

		if (unlikely(!page_evictable(page))) {
			putback_lru_page(page);
			continue;
		}

		if (unlikely(buffer_heads_over_limit)) {
			if (page_has_private(page) && trylock_page(page)) {
				if (page_has_private(page))
					try_to_release_page(page, 0);
				unlock_page(page);
			}
		}

		if (page_referenced(page, 0, sc->target_mem_cgroup,
				    &vm_flags)) {
			nr_rotated += hpage_nr_pages(page);
			/*
			 * Identify referenced, file-backed active pages and
			 * give them one more trip around the active list. So
			 * that executable code get better chances to stay in
			 * memory under moderate memory pressure.  Anon pages
			 * are not likely to be evicted by use-once streaming
			 * IO, plus JVM can create lots of anon VM_EXEC pages,
			 * so we ignore them here.
			 */
			if ((vm_flags & VM_EXEC) && page_is_file_cache(page)) {
				list_add(&page->lru, &l_active);
				continue;
			}
		}

		ClearPageActive(page);	/* we are de-activating */
		list_add(&page->lru, &l_inactive);
	}

	/*
	 * Move pages back to the lru list.
	 */
	spin_lock_irq(&pgdat->lru_lock);
	/*
	 * Count referenced pages from currently used mappings as rotated,
	 * even though only some of them are actually re-activated.  This
	 * helps balance scan pressure between file and anonymous pages in
	 * get_scan_count.
	 */
	reclaim_stat->recent_rotated[file] += nr_rotated;

	nr_activate = move_active_pages_to_lru(lruvec, &l_active, &l_hold, lru);
	nr_deactivate = move_active_pages_to_lru(lruvec, &l_inactive, &l_hold, lru - LRU_ACTIVE);
	__mod_node_page_state(pgdat, NR_ISOLATED_ANON + file, -nr_taken);
	spin_unlock_irq(&pgdat->lru_lock);

	mem_cgroup_uncharge_list(&l_hold);
	free_unref_page_list(&l_hold);
	trace_mm_vmscan_lru_shrink_active(pgdat->node_id, nr_taken, nr_activate,
			nr_deactivate, nr_rotated, sc->priority, file);
}