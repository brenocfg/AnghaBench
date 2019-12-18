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
 int /*<<< orphan*/  HPAGE_PMD_ORDER ; 
 int /*<<< orphan*/  alloc_hugepage_khugepaged_gfpmask () ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prep_transhuge_page (struct page*) ; 

__attribute__((used)) static inline struct page *alloc_khugepaged_hugepage(void)
{
	struct page *page;

	page = alloc_pages(alloc_hugepage_khugepaged_gfpmask(),
			   HPAGE_PMD_ORDER);
	if (page)
		prep_transhuge_page(page);
	return page;
}