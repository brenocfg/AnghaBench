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
 int /*<<< orphan*/  ClearPageLRU (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct page*,struct lruvec*,int /*<<< orphan*/ ) ; 
 struct lruvec* mem_cgroup_page_lruvec (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_lru (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_lru_lock (struct zone*) ; 

__attribute__((used)) static void lock_page_lru(struct page *page, int *isolated)
{
	struct zone *zone = page_zone(page);

	spin_lock_irq(zone_lru_lock(zone));
	if (PageLRU(page)) {
		struct lruvec *lruvec;

		lruvec = mem_cgroup_page_lruvec(page, zone->zone_pgdat);
		ClearPageLRU(page);
		del_page_from_lru_list(page, lruvec, page_lru(page));
		*isolated = 1;
	} else
		*isolated = 0;
}