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

/* Variables and functions */
 int HPAGE_PMD_NR ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 int page_count (struct page*) ; 
 int page_has_private (struct page*) ; 

__attribute__((used)) static inline int is_page_cache_freeable(struct page *page)
{
	/*
	 * A freeable page cache page is referenced only by the caller
	 * that isolated the page, the page cache and optional buffer
	 * heads at page->private.
	 */
	int page_cache_pins = PageTransHuge(page) && PageSwapCache(page) ?
		HPAGE_PMD_NR : 1;
	return page_count(page) - page_has_private(page) == 1 + page_cache_pins;
}