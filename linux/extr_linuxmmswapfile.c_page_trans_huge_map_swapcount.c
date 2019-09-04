#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct swap_info_struct {unsigned char* swap_map; } ;
struct swap_cluster_info {int dummy; } ;
struct page {int /*<<< orphan*/  _mapcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_THP_SWAP ; 
 int HPAGE_PMD_NR ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ PageDoubleMap (struct page*) ; 
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  PageTransCompound (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int /*<<< orphan*/ ,struct page*) ; 
 struct swap_info_struct* _swap_info_get (TYPE_1__) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct page* compound_head (struct page*) ; 
 int compound_mapcount (struct page*) ; 
 scalar_t__ likely (int) ; 
 struct swap_cluster_info* lock_cluster (struct swap_info_struct*,unsigned long) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int page_swapcount (struct page*) ; 
 int page_trans_huge_mapcount (struct page*,int*) ; 
 int swap_count (unsigned char) ; 
 unsigned long swp_offset (TYPE_1__) ; 
 int /*<<< orphan*/  unlock_cluster (struct swap_cluster_info*) ; 

__attribute__((used)) static int page_trans_huge_map_swapcount(struct page *page, int *total_mapcount,
					 int *total_swapcount)
{
	int i, map_swapcount, _total_mapcount, _total_swapcount;
	unsigned long offset = 0;
	struct swap_info_struct *si;
	struct swap_cluster_info *ci = NULL;
	unsigned char *map = NULL;
	int mapcount, swapcount = 0;

	/* hugetlbfs shouldn't call it */
	VM_BUG_ON_PAGE(PageHuge(page), page);

	if (!IS_ENABLED(CONFIG_THP_SWAP) || likely(!PageTransCompound(page))) {
		mapcount = page_trans_huge_mapcount(page, total_mapcount);
		if (PageSwapCache(page))
			swapcount = page_swapcount(page);
		if (total_swapcount)
			*total_swapcount = swapcount;
		return mapcount + swapcount;
	}

	page = compound_head(page);

	_total_mapcount = _total_swapcount = map_swapcount = 0;
	if (PageSwapCache(page)) {
		swp_entry_t entry;

		entry.val = page_private(page);
		si = _swap_info_get(entry);
		if (si) {
			map = si->swap_map;
			offset = swp_offset(entry);
		}
	}
	if (map)
		ci = lock_cluster(si, offset);
	for (i = 0; i < HPAGE_PMD_NR; i++) {
		mapcount = atomic_read(&page[i]._mapcount) + 1;
		_total_mapcount += mapcount;
		if (map) {
			swapcount = swap_count(map[offset + i]);
			_total_swapcount += swapcount;
		}
		map_swapcount = max(map_swapcount, mapcount + swapcount);
	}
	unlock_cluster(ci);
	if (PageDoubleMap(page)) {
		map_swapcount -= 1;
		_total_mapcount -= HPAGE_PMD_NR;
	}
	mapcount = compound_mapcount(page);
	map_swapcount += mapcount;
	_total_mapcount += mapcount;
	if (total_mapcount)
		*total_mapcount = _total_mapcount;
	if (total_swapcount)
		*total_swapcount = _total_swapcount;

	return map_swapcount;
}