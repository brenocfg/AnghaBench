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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/ * get_locked_pte (struct mm_struct*,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  maybe_mkwrite (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 scalar_t__ pfn_t_devmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_t_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_t_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkdevmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkspecial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkyoung (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_mmu_cache (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int insert_pfn(struct vm_area_struct *vma, unsigned long addr,
			pfn_t pfn, pgprot_t prot, bool mkwrite)
{
	struct mm_struct *mm = vma->vm_mm;
	int retval;
	pte_t *pte, entry;
	spinlock_t *ptl;

	retval = -ENOMEM;
	pte = get_locked_pte(mm, addr, &ptl);
	if (!pte)
		goto out;
	retval = -EBUSY;
	if (!pte_none(*pte)) {
		if (mkwrite) {
			/*
			 * For read faults on private mappings the PFN passed
			 * in may not match the PFN we have mapped if the
			 * mapped PFN is a writeable COW page.  In the mkwrite
			 * case we are creating a writable PTE for a shared
			 * mapping and we expect the PFNs to match.
			 */
			if (WARN_ON_ONCE(pte_pfn(*pte) != pfn_t_to_pfn(pfn)))
				goto out_unlock;
			entry = *pte;
			goto out_mkwrite;
		} else
			goto out_unlock;
	}

	/* Ok, finally just insert the thing.. */
	if (pfn_t_devmap(pfn))
		entry = pte_mkdevmap(pfn_t_pte(pfn, prot));
	else
		entry = pte_mkspecial(pfn_t_pte(pfn, prot));

out_mkwrite:
	if (mkwrite) {
		entry = pte_mkyoung(entry);
		entry = maybe_mkwrite(pte_mkdirty(entry), vma);
	}

	set_pte_at(mm, addr, pte, entry);
	update_mmu_cache(vma, addr, pte); /* XXX: why not for insert_page? */

	retval = 0;
out_unlock:
	pte_unmap_unlock(pte, ptl);
out:
	return retval;
}