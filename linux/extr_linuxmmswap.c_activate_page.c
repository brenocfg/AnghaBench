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

/* Variables and functions */
 int /*<<< orphan*/  __activate_page (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_page_lruvec (struct page*,int /*<<< orphan*/ ) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_lru_lock (struct zone*) ; 

void activate_page(struct page *page)
{
	struct zone *zone = page_zone(page);

	page = compound_head(page);
	spin_lock_irq(zone_lru_lock(zone));
	__activate_page(page, mem_cgroup_page_lruvec(page, zone->zone_pgdat), NULL);
	spin_unlock_irq(zone_lru_lock(zone));
}