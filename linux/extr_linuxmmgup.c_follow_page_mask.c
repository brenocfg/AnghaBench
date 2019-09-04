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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned int) ; 
 unsigned int FOLL_GET ; 
 unsigned int FOLL_WRITE ; 
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 int /*<<< orphan*/  PGDIR_SHIFT ; 
 int /*<<< orphan*/  __hugepd (int /*<<< orphan*/ ) ; 
 struct page* follow_huge_addr (struct mm_struct*,unsigned long,unsigned int) ; 
 struct page* follow_huge_pd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct page* follow_huge_pgd (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 struct page* follow_p4d_mask (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int,unsigned int*) ; 
 scalar_t__ is_hugepd (int /*<<< orphan*/ ) ; 
 struct page* no_page_table (struct vm_area_struct*,unsigned int) ; 
 int /*<<< orphan*/  pgd_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pgd_val (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct page *follow_page_mask(struct vm_area_struct *vma,
			      unsigned long address, unsigned int flags,
			      unsigned int *page_mask)
{
	pgd_t *pgd;
	struct page *page;
	struct mm_struct *mm = vma->vm_mm;

	*page_mask = 0;

	/* make this handle hugepd */
	page = follow_huge_addr(mm, address, flags & FOLL_WRITE);
	if (!IS_ERR(page)) {
		BUG_ON(flags & FOLL_GET);
		return page;
	}

	pgd = pgd_offset(mm, address);

	if (pgd_none(*pgd) || unlikely(pgd_bad(*pgd)))
		return no_page_table(vma, flags);

	if (pgd_huge(*pgd)) {
		page = follow_huge_pgd(mm, address, pgd, flags);
		if (page)
			return page;
		return no_page_table(vma, flags);
	}
	if (is_hugepd(__hugepd(pgd_val(*pgd)))) {
		page = follow_huge_pd(vma, address,
				      __hugepd(pgd_val(*pgd)), flags,
				      PGDIR_SHIFT);
		if (page)
			return page;
		return no_page_table(vma, flags);
	}

	return follow_p4d_mask(vma, address, pgd, flags, page_mask);
}