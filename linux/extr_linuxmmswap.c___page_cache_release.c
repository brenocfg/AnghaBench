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
struct zone {int /*<<< orphan*/  zone_pgdat; } ;
struct page {int dummy; } ;
struct lruvec {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  __ClearPageLRU (struct page*) ; 
 int /*<<< orphan*/  __ClearPageWaiters (struct page*) ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct page*,struct lruvec*,int /*<<< orphan*/ ) ; 
 struct lruvec* mem_cgroup_page_lruvec (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge (struct page*) ; 
 int /*<<< orphan*/  page_off_lru (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  zone_lru_lock (struct zone*) ; 

__attribute__((used)) static void __page_cache_release(struct page *page)
{
	if (PageLRU(page)) {
		struct zone *zone = page_zone(page);
		struct lruvec *lruvec;
		unsigned long flags;

		spin_lock_irqsave(zone_lru_lock(zone), flags);
		lruvec = mem_cgroup_page_lruvec(page, zone->zone_pgdat);
		VM_BUG_ON_PAGE(!PageLRU(page), page);
		__ClearPageLRU(page);
		del_page_from_lru_list(page, lruvec, page_off_lru(page));
		spin_unlock_irqrestore(zone_lru_lock(zone), flags);
	}
	__ClearPageWaiters(page);
	mem_cgroup_uncharge(page);
}