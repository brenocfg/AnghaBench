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
 int IOMMU_WRITE ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  is_invalid_reserved_pfn (unsigned long) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int put_pfn(unsigned long pfn, int prot)
{
	if (!is_invalid_reserved_pfn(pfn)) {
		struct page *page = pfn_to_page(pfn);
		if (prot & IOMMU_WRITE)
			SetPageDirty(page);
		put_page(page);
		return 1;
	}
	return 0;
}