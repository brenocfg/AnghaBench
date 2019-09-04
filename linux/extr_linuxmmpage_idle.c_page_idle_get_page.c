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
struct zone {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageLRU (struct page*) ; 
 int /*<<< orphan*/  get_page_unless_zero (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zone_lru_lock (struct zone*) ; 

__attribute__((used)) static struct page *page_idle_get_page(unsigned long pfn)
{
	struct page *page;
	struct zone *zone;

	if (!pfn_valid(pfn))
		return NULL;

	page = pfn_to_page(pfn);
	if (!page || !PageLRU(page) ||
	    !get_page_unless_zero(page))
		return NULL;

	zone = page_zone(page);
	spin_lock_irq(zone_lru_lock(zone));
	if (unlikely(!PageLRU(page))) {
		put_page(page);
		page = NULL;
	}
	spin_unlock_irq(zone_lru_lock(zone));
	return page;
}