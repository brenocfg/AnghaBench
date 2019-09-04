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
 unsigned long page_to_pfn (struct page*) ; 
 scalar_t__ pfn_to_kaddr (unsigned long) ; 

__attribute__((used)) static unsigned long vaddr_page(struct page *page)
{
	unsigned long pfn = page_to_pfn(page);

	return (unsigned long)pfn_to_kaddr(pfn);
}