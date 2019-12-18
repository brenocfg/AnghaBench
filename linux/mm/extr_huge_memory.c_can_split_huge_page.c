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
 scalar_t__ PageAnon (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int page_count (struct page*) ; 
 int total_mapcount (struct page*) ; 

bool can_split_huge_page(struct page *page, int *pextra_pins)
{
	int extra_pins;

	/* Additional pins from page cache */
	if (PageAnon(page))
		extra_pins = PageSwapCache(page) ? HPAGE_PMD_NR : 0;
	else
		extra_pins = HPAGE_PMD_NR;
	if (pextra_pins)
		*pextra_pins = extra_pins;
	return total_mapcount(page) == page_count(page) - extra_pins - 1;
}