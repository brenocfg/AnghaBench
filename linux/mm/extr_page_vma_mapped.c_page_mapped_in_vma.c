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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; } ;
struct page_vma_mapped_walk {int /*<<< orphan*/  address; int /*<<< orphan*/  flags; struct vm_area_struct* vma; struct page* page; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PVMW_SYNC ; 
 unsigned long __vma_address (struct page*,struct vm_area_struct*) ; 
 int hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  max (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  page_vma_mapped_walk (struct page_vma_mapped_walk*) ; 
 int /*<<< orphan*/  page_vma_mapped_walk_done (struct page_vma_mapped_walk*) ; 
 scalar_t__ unlikely (int) ; 

int page_mapped_in_vma(struct page *page, struct vm_area_struct *vma)
{
	struct page_vma_mapped_walk pvmw = {
		.page = page,
		.vma = vma,
		.flags = PVMW_SYNC,
	};
	unsigned long start, end;

	start = __vma_address(page, vma);
	end = start + PAGE_SIZE * (hpage_nr_pages(page) - 1);

	if (unlikely(end < vma->vm_start || start >= vma->vm_end))
		return 0;
	pvmw.address = max(start, vma->vm_start);
	if (!page_vma_mapped_walk(&pvmw))
		return 0;
	page_vma_mapped_walk_done(&pvmw);
	return 1;
}