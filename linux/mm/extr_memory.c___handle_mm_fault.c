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
typedef  int vm_fault_t ;
struct vm_fault {unsigned long address; unsigned int flags; int /*<<< orphan*/ * pmd; int /*<<< orphan*/ * pud; int /*<<< orphan*/  gfp_mask; int /*<<< orphan*/  pgoff; struct vm_area_struct* vma; } ;
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 unsigned int FAULT_FLAG_WRITE ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int VM_FAULT_FALLBACK ; 
 int VM_FAULT_OOM ; 
 int /*<<< orphan*/  __get_fault_gfp_mask (struct vm_area_struct*) ; 
 scalar_t__ __transparent_hugepage_enabled (struct vm_area_struct*) ; 
 int /*<<< orphan*/  barrier () ; 
 int create_huge_pmd (struct vm_fault*) ; 
 int create_huge_pud (struct vm_fault*) ; 
 int do_huge_pmd_numa_page (struct vm_fault*,int /*<<< orphan*/ ) ; 
 int handle_pte_fault (struct vm_fault*) ; 
 int /*<<< orphan*/  huge_pmd_set_accessed (struct vm_fault*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_pud_set_accessed (struct vm_fault*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_pmd_migration_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_swap_pmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linear_page_index (struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/ * p4d_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_devmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_migration_entry_wait (struct mm_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_protnone (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_devmap (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_write (int /*<<< orphan*/ ) ; 
 scalar_t__ thp_migration_supported () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vma_is_accessible (struct vm_area_struct*) ; 
 int wp_huge_pmd (struct vm_fault*,int /*<<< orphan*/ ) ; 
 int wp_huge_pud (struct vm_fault*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t __handle_mm_fault(struct vm_area_struct *vma,
		unsigned long address, unsigned int flags)
{
	struct vm_fault vmf = {
		.vma = vma,
		.address = address & PAGE_MASK,
		.flags = flags,
		.pgoff = linear_page_index(vma, address),
		.gfp_mask = __get_fault_gfp_mask(vma),
	};
	unsigned int dirty = flags & FAULT_FLAG_WRITE;
	struct mm_struct *mm = vma->vm_mm;
	pgd_t *pgd;
	p4d_t *p4d;
	vm_fault_t ret;

	pgd = pgd_offset(mm, address);
	p4d = p4d_alloc(mm, pgd, address);
	if (!p4d)
		return VM_FAULT_OOM;

	vmf.pud = pud_alloc(mm, p4d, address);
	if (!vmf.pud)
		return VM_FAULT_OOM;
	if (pud_none(*vmf.pud) && __transparent_hugepage_enabled(vma)) {
		ret = create_huge_pud(&vmf);
		if (!(ret & VM_FAULT_FALLBACK))
			return ret;
	} else {
		pud_t orig_pud = *vmf.pud;

		barrier();
		if (pud_trans_huge(orig_pud) || pud_devmap(orig_pud)) {

			/* NUMA case for anonymous PUDs would go here */

			if (dirty && !pud_write(orig_pud)) {
				ret = wp_huge_pud(&vmf, orig_pud);
				if (!(ret & VM_FAULT_FALLBACK))
					return ret;
			} else {
				huge_pud_set_accessed(&vmf, orig_pud);
				return 0;
			}
		}
	}

	vmf.pmd = pmd_alloc(mm, vmf.pud, address);
	if (!vmf.pmd)
		return VM_FAULT_OOM;
	if (pmd_none(*vmf.pmd) && __transparent_hugepage_enabled(vma)) {
		ret = create_huge_pmd(&vmf);
		if (!(ret & VM_FAULT_FALLBACK))
			return ret;
	} else {
		pmd_t orig_pmd = *vmf.pmd;

		barrier();
		if (unlikely(is_swap_pmd(orig_pmd))) {
			VM_BUG_ON(thp_migration_supported() &&
					  !is_pmd_migration_entry(orig_pmd));
			if (is_pmd_migration_entry(orig_pmd))
				pmd_migration_entry_wait(mm, vmf.pmd);
			return 0;
		}
		if (pmd_trans_huge(orig_pmd) || pmd_devmap(orig_pmd)) {
			if (pmd_protnone(orig_pmd) && vma_is_accessible(vma))
				return do_huge_pmd_numa_page(&vmf, orig_pmd);

			if (dirty && !pmd_write(orig_pmd)) {
				ret = wp_huge_pmd(&vmf, orig_pmd);
				if (!(ret & VM_FAULT_FALLBACK))
					return ret;
			} else {
				huge_pmd_set_accessed(&vmf, orig_pmd);
				return 0;
			}
		}
	}

	return handle_pte_fault(&vmf);
}