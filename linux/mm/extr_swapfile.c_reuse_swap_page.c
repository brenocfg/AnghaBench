#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct swap_info_struct {int flags; int /*<<< orphan*/  lock; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageKsm (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  PageTransCompound (struct page*) ; 
 int /*<<< orphan*/  PageWriteback (struct page*) ; 
 int SWP_STABLE_WRITES ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  delete_from_swap_cache (struct page*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int page_swapcount (struct page*) ; 
 int page_trans_huge_map_swapcount (struct page*,int*,int*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct swap_info_struct* swap_info_get (TYPE_1__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

bool reuse_swap_page(struct page *page, int *total_map_swapcount)
{
	int count, total_mapcount, total_swapcount;

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	if (unlikely(PageKsm(page)))
		return false;
	count = page_trans_huge_map_swapcount(page, &total_mapcount,
					      &total_swapcount);
	if (total_map_swapcount)
		*total_map_swapcount = total_mapcount + total_swapcount;
	if (count == 1 && PageSwapCache(page) &&
	    (likely(!PageTransCompound(page)) ||
	     /* The remaining swap count will be freed soon */
	     total_swapcount == page_swapcount(page))) {
		if (!PageWriteback(page)) {
			page = compound_head(page);
			delete_from_swap_cache(page);
			SetPageDirty(page);
		} else {
			swp_entry_t entry;
			struct swap_info_struct *p;

			entry.val = page_private(page);
			p = swap_info_get(entry);
			if (p->flags & SWP_STABLE_WRITES) {
				spin_unlock(&p->lock);
				return false;
			}
			spin_unlock(&p->lock);
		}
	}

	return count <= 1;
}