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
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ PageAnon (struct page*) ; 
 scalar_t__ PageSlab (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/ * get_locked_pte (struct mm_struct*,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  inc_mm_counter_fast (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_counter_file (struct page*) ; 
 int /*<<< orphan*/  page_add_file_rmap (struct page*,int) ; 
 scalar_t__ page_has_type (struct page*) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int insert_page(struct vm_area_struct *vma, unsigned long addr,
			struct page *page, pgprot_t prot)
{
	struct mm_struct *mm = vma->vm_mm;
	int retval;
	pte_t *pte;
	spinlock_t *ptl;

	retval = -EINVAL;
	if (PageAnon(page) || PageSlab(page) || page_has_type(page))
		goto out;
	retval = -ENOMEM;
	flush_dcache_page(page);
	pte = get_locked_pte(mm, addr, &ptl);
	if (!pte)
		goto out;
	retval = -EBUSY;
	if (!pte_none(*pte))
		goto out_unlock;

	/* Ok, finally just insert the thing.. */
	get_page(page);
	inc_mm_counter_fast(mm, mm_counter_file(page));
	page_add_file_rmap(page, false);
	set_pte_at(mm, addr, pte, mk_pte(page, prot));

	retval = 0;
out_unlock:
	pte_unmap_unlock(pte, ptl);
out:
	return retval;
}