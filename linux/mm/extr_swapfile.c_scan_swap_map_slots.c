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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct swap_info_struct {int flags; unsigned long cluster_next; int cluster_nr; int pages; int inuse_pages; unsigned long lowest_bit; unsigned long highest_bit; char* swap_map; int /*<<< orphan*/  lock; scalar_t__ cluster_info; int /*<<< orphan*/  type; } ;
struct swap_cluster_info {int dummy; } ;

/* Variables and functions */
 int LATENCY_LIMIT ; 
 int SWAPFILE_CLUSTER ; 
 int SWAP_BATCH ; 
 char SWAP_HAS_CACHE ; 
 scalar_t__ SWP_SCANNING ; 
 int SWP_WRITEOK ; 
 int /*<<< orphan*/  TTRS_ANYWAY ; 
 int __try_to_reclaim_swap (struct swap_info_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  inc_cluster_info_page (struct swap_info_struct*,scalar_t__,unsigned long) ; 
 struct swap_cluster_info* lock_cluster (struct swap_info_struct*,unsigned long) ; 
 scalar_t__ scan_swap_map_ssd_cluster_conflict (struct swap_info_struct*,unsigned long) ; 
 scalar_t__ scan_swap_map_try_ssd_cluster (struct swap_info_struct*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_range_alloc (struct swap_info_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  swp_entry (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_cluster (struct swap_cluster_info*) ; 
 scalar_t__ vm_swap_full () ; 

__attribute__((used)) static int scan_swap_map_slots(struct swap_info_struct *si,
			       unsigned char usage, int nr,
			       swp_entry_t slots[])
{
	struct swap_cluster_info *ci;
	unsigned long offset;
	unsigned long scan_base;
	unsigned long last_in_cluster = 0;
	int latency_ration = LATENCY_LIMIT;
	int n_ret = 0;

	if (nr > SWAP_BATCH)
		nr = SWAP_BATCH;

	/*
	 * We try to cluster swap pages by allocating them sequentially
	 * in swap.  Once we've allocated SWAPFILE_CLUSTER pages this
	 * way, however, we resort to first-free allocation, starting
	 * a new cluster.  This prevents us from scattering swap pages
	 * all over the entire swap partition, so that we reduce
	 * overall disk seek times between swap pages.  -- sct
	 * But we do now try to find an empty cluster.  -Andrea
	 * And we let swap pages go all over an SSD partition.  Hugh
	 */

	si->flags += SWP_SCANNING;
	scan_base = offset = si->cluster_next;

	/* SSD algorithm */
	if (si->cluster_info) {
		if (scan_swap_map_try_ssd_cluster(si, &offset, &scan_base))
			goto checks;
		else
			goto scan;
	}

	if (unlikely(!si->cluster_nr--)) {
		if (si->pages - si->inuse_pages < SWAPFILE_CLUSTER) {
			si->cluster_nr = SWAPFILE_CLUSTER - 1;
			goto checks;
		}

		spin_unlock(&si->lock);

		/*
		 * If seek is expensive, start searching for new cluster from
		 * start of partition, to minimize the span of allocated swap.
		 * If seek is cheap, that is the SWP_SOLIDSTATE si->cluster_info
		 * case, just handled by scan_swap_map_try_ssd_cluster() above.
		 */
		scan_base = offset = si->lowest_bit;
		last_in_cluster = offset + SWAPFILE_CLUSTER - 1;

		/* Locate the first empty (unaligned) cluster */
		for (; last_in_cluster <= si->highest_bit; offset++) {
			if (si->swap_map[offset])
				last_in_cluster = offset + SWAPFILE_CLUSTER;
			else if (offset == last_in_cluster) {
				spin_lock(&si->lock);
				offset -= SWAPFILE_CLUSTER - 1;
				si->cluster_next = offset;
				si->cluster_nr = SWAPFILE_CLUSTER - 1;
				goto checks;
			}
			if (unlikely(--latency_ration < 0)) {
				cond_resched();
				latency_ration = LATENCY_LIMIT;
			}
		}

		offset = scan_base;
		spin_lock(&si->lock);
		si->cluster_nr = SWAPFILE_CLUSTER - 1;
	}

checks:
	if (si->cluster_info) {
		while (scan_swap_map_ssd_cluster_conflict(si, offset)) {
		/* take a break if we already got some slots */
			if (n_ret)
				goto done;
			if (!scan_swap_map_try_ssd_cluster(si, &offset,
							&scan_base))
				goto scan;
		}
	}
	if (!(si->flags & SWP_WRITEOK))
		goto no_page;
	if (!si->highest_bit)
		goto no_page;
	if (offset > si->highest_bit)
		scan_base = offset = si->lowest_bit;

	ci = lock_cluster(si, offset);
	/* reuse swap entry of cache-only swap if not busy. */
	if (vm_swap_full() && si->swap_map[offset] == SWAP_HAS_CACHE) {
		int swap_was_freed;
		unlock_cluster(ci);
		spin_unlock(&si->lock);
		swap_was_freed = __try_to_reclaim_swap(si, offset, TTRS_ANYWAY);
		spin_lock(&si->lock);
		/* entry was freed successfully, try to use this again */
		if (swap_was_freed)
			goto checks;
		goto scan; /* check next one */
	}

	if (si->swap_map[offset]) {
		unlock_cluster(ci);
		if (!n_ret)
			goto scan;
		else
			goto done;
	}
	si->swap_map[offset] = usage;
	inc_cluster_info_page(si, si->cluster_info, offset);
	unlock_cluster(ci);

	swap_range_alloc(si, offset, 1);
	si->cluster_next = offset + 1;
	slots[n_ret++] = swp_entry(si->type, offset);

	/* got enough slots or reach max slots? */
	if ((n_ret == nr) || (offset >= si->highest_bit))
		goto done;

	/* search for next available slot */

	/* time to take a break? */
	if (unlikely(--latency_ration < 0)) {
		if (n_ret)
			goto done;
		spin_unlock(&si->lock);
		cond_resched();
		spin_lock(&si->lock);
		latency_ration = LATENCY_LIMIT;
	}

	/* try to get more slots in cluster */
	if (si->cluster_info) {
		if (scan_swap_map_try_ssd_cluster(si, &offset, &scan_base))
			goto checks;
		else
			goto done;
	}
	/* non-ssd case */
	++offset;

	/* non-ssd case, still more slots in cluster? */
	if (si->cluster_nr && !si->swap_map[offset]) {
		--si->cluster_nr;
		goto checks;
	}

done:
	si->flags -= SWP_SCANNING;
	return n_ret;

scan:
	spin_unlock(&si->lock);
	while (++offset <= si->highest_bit) {
		if (!si->swap_map[offset]) {
			spin_lock(&si->lock);
			goto checks;
		}
		if (vm_swap_full() && si->swap_map[offset] == SWAP_HAS_CACHE) {
			spin_lock(&si->lock);
			goto checks;
		}
		if (unlikely(--latency_ration < 0)) {
			cond_resched();
			latency_ration = LATENCY_LIMIT;
		}
	}
	offset = si->lowest_bit;
	while (offset < scan_base) {
		if (!si->swap_map[offset]) {
			spin_lock(&si->lock);
			goto checks;
		}
		if (vm_swap_full() && si->swap_map[offset] == SWAP_HAS_CACHE) {
			spin_lock(&si->lock);
			goto checks;
		}
		if (unlikely(--latency_ration < 0)) {
			cond_resched();
			latency_ration = LATENCY_LIMIT;
		}
		offset++;
	}
	spin_lock(&si->lock);

no_page:
	si->flags -= SWP_SCANNING;
	return n_ret;
}