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
struct dev_pagemap {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EFAULT ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 int FOLL_COW ; 
 int FOLL_GET ; 
 int FOLL_TOUCH ; 
 int FOLL_WRITE ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PMD_MASK ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ ) ; 
 struct dev_pagemap* get_dev_pagemap (unsigned long,struct dev_pagemap*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 
 scalar_t__ pmd_devmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_lockptr (struct mm_struct*,int /*<<< orphan*/ *) ; 
 unsigned long pmd_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch_pmd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int) ; 

struct page *follow_devmap_pmd(struct vm_area_struct *vma, unsigned long addr,
		pmd_t *pmd, int flags, struct dev_pagemap **pgmap)
{
	unsigned long pfn = pmd_pfn(*pmd);
	struct mm_struct *mm = vma->vm_mm;
	struct page *page;

	assert_spin_locked(pmd_lockptr(mm, pmd));

	/*
	 * When we COW a devmap PMD entry, we split it into PTEs, so we should
	 * not be in this function with `flags & FOLL_COW` set.
	 */
	WARN_ONCE(flags & FOLL_COW, "mm: In follow_devmap_pmd with FOLL_COW set");

	if (flags & FOLL_WRITE && !pmd_write(*pmd))
		return NULL;

	if (pmd_present(*pmd) && pmd_devmap(*pmd))
		/* pass */;
	else
		return NULL;

	if (flags & FOLL_TOUCH)
		touch_pmd(vma, addr, pmd, flags);

	/*
	 * device mapped pages can only be returned if the
	 * caller will manage the page reference count.
	 */
	if (!(flags & FOLL_GET))
		return ERR_PTR(-EEXIST);

	pfn += (addr & ~PMD_MASK) >> PAGE_SHIFT;
	*pgmap = get_dev_pagemap(pfn, *pgmap);
	if (!*pgmap)
		return ERR_PTR(-EFAULT);
	page = pfn_to_page(pfn);
	get_page(page);

	return page;
}