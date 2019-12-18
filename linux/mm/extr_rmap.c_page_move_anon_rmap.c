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
struct page {int /*<<< orphan*/  mapping; } ;
struct anon_vma {int dummy; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int PAGE_MAPPING_ANON ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_VMA (int,struct vm_area_struct*) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,struct address_space*) ; 
 struct page* compound_head (struct page*) ; 

void page_move_anon_rmap(struct page *page, struct vm_area_struct *vma)
{
	struct anon_vma *anon_vma = vma->anon_vma;

	page = compound_head(page);

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_VMA(!anon_vma, vma);

	anon_vma = (void *) anon_vma + PAGE_MAPPING_ANON;
	/*
	 * Ensure that anon_vma and the PAGE_MAPPING_ANON bit are written
	 * simultaneously, so a concurrent reader (eg page_referenced()'s
	 * PageAnon()) will not see one without the other.
	 */
	WRITE_ONCE(page->mapping, (struct address_space *) anon_vma);
}