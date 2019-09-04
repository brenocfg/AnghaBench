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
struct vm_area_struct {int vm_flags; struct mm_struct* vm_mm; } ;
struct page {scalar_t__ mapping; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int FOLL_DUMP ; 
 unsigned int FOLL_GET ; 
 unsigned int FOLL_MLOCK ; 
 unsigned int FOLL_NUMA ; 
 unsigned int FOLL_TOUCH ; 
 unsigned int FOLL_WRITE ; 
 unsigned long HPAGE_PMD_MASK ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 scalar_t__ PageDoubleMap (struct page*) ; 
 int /*<<< orphan*/  PageHead (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int VM_LOCKED ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_follow_write_pmd (int /*<<< orphan*/ ,unsigned int) ; 
 int compound_mapcount (struct page*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ is_huge_zero_pmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zone_device_page (struct page*) ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  mlock_vma_page (struct page*) ; 
 int /*<<< orphan*/  pmd_lockptr (struct mm_struct*,int /*<<< orphan*/ *) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_protnone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch_pmd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

struct page *follow_trans_huge_pmd(struct vm_area_struct *vma,
				   unsigned long addr,
				   pmd_t *pmd,
				   unsigned int flags)
{
	struct mm_struct *mm = vma->vm_mm;
	struct page *page = NULL;

	assert_spin_locked(pmd_lockptr(mm, pmd));

	if (flags & FOLL_WRITE && !can_follow_write_pmd(*pmd, flags))
		goto out;

	/* Avoid dumping huge zero page */
	if ((flags & FOLL_DUMP) && is_huge_zero_pmd(*pmd))
		return ERR_PTR(-EFAULT);

	/* Full NUMA hinting faults to serialise migration in fault paths */
	if ((flags & FOLL_NUMA) && pmd_protnone(*pmd))
		goto out;

	page = pmd_page(*pmd);
	VM_BUG_ON_PAGE(!PageHead(page) && !is_zone_device_page(page), page);
	if (flags & FOLL_TOUCH)
		touch_pmd(vma, addr, pmd, flags);
	if ((flags & FOLL_MLOCK) && (vma->vm_flags & VM_LOCKED)) {
		/*
		 * We don't mlock() pte-mapped THPs. This way we can avoid
		 * leaking mlocked pages into non-VM_LOCKED VMAs.
		 *
		 * For anon THP:
		 *
		 * In most cases the pmd is the only mapping of the page as we
		 * break COW for the mlock() -- see gup_flags |= FOLL_WRITE for
		 * writable private mappings in populate_vma_page_range().
		 *
		 * The only scenario when we have the page shared here is if we
		 * mlocking read-only mapping shared over fork(). We skip
		 * mlocking such pages.
		 *
		 * For file THP:
		 *
		 * We can expect PageDoubleMap() to be stable under page lock:
		 * for file pages we set it in page_add_file_rmap(), which
		 * requires page to be locked.
		 */

		if (PageAnon(page) && compound_mapcount(page) != 1)
			goto skip_mlock;
		if (PageDoubleMap(page) || !page->mapping)
			goto skip_mlock;
		if (!trylock_page(page))
			goto skip_mlock;
		lru_add_drain();
		if (page->mapping && !PageDoubleMap(page))
			mlock_vma_page(page);
		unlock_page(page);
	}
skip_mlock:
	page += (addr & ~HPAGE_PMD_MASK) >> PAGE_SHIFT;
	VM_BUG_ON_PAGE(!PageCompound(page) && !is_zone_device_page(page), page);
	if (flags & FOLL_GET)
		get_page(page);

out:
	return page;
}