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
struct vm_area_struct {struct anon_vma* anon_vma; } ;
struct page {int /*<<< orphan*/  index; struct address_space* mapping; } ;
struct anon_vma {struct anon_vma* root; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_MAPPING_ANON ; 
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  linear_page_index (struct vm_area_struct*,unsigned long) ; 

__attribute__((used)) static void __page_set_anon_rmap(struct page *page,
	struct vm_area_struct *vma, unsigned long address, int exclusive)
{
	struct anon_vma *anon_vma = vma->anon_vma;

	BUG_ON(!anon_vma);

	if (PageAnon(page))
		return;

	/*
	 * If the page isn't exclusively mapped into this vma,
	 * we must use the _oldest_ possible anon_vma for the
	 * page mapping!
	 */
	if (!exclusive)
		anon_vma = anon_vma->root;

	anon_vma = (void *) anon_vma + PAGE_MAPPING_ANON;
	page->mapping = (struct address_space *) anon_vma;
	page->index = linear_page_index(vma, address);
}