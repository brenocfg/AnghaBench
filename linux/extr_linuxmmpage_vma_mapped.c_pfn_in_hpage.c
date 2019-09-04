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
 unsigned long hpage_nr_pages (struct page*) ; 
 unsigned long page_to_pfn (struct page*) ; 

__attribute__((used)) static inline bool pfn_in_hpage(struct page *hpage, unsigned long pfn)
{
	unsigned long hpage_pfn = page_to_pfn(hpage);

	/* THP can be referenced by any subpage */
	return pfn >= hpage_pfn && pfn - hpage_pfn < hpage_nr_pages(hpage);
}