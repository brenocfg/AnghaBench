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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 scalar_t__ PageOffline (struct page*) ; 
 scalar_t__ PageReserved (struct page*) ; 
 int /*<<< orphan*/  kernel_page_present (struct page*) ; 
 scalar_t__ page_is_guard (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 scalar_t__ pfn_is_nosave (unsigned long) ; 
 struct page* pfn_to_online_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 scalar_t__ swsusp_page_is_forbidden (struct page*) ; 
 scalar_t__ swsusp_page_is_free (struct page*) ; 

__attribute__((used)) static struct page *saveable_page(struct zone *zone, unsigned long pfn)
{
	struct page *page;

	if (!pfn_valid(pfn))
		return NULL;

	page = pfn_to_online_page(pfn);
	if (!page || page_zone(page) != zone)
		return NULL;

	BUG_ON(PageHighMem(page));

	if (swsusp_page_is_forbidden(page) || swsusp_page_is_free(page))
		return NULL;

	if (PageOffline(page))
		return NULL;

	if (PageReserved(page)
	    && (!kernel_page_present(page) || pfn_is_nosave(pfn)))
		return NULL;

	if (page_is_guard(page))
		return NULL;

	return page;
}