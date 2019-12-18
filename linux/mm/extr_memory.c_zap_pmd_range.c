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
struct zap_details {int dummy; } ;
struct vm_area_struct {int dummy; } ;
struct mmu_gather {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  __split_huge_pmd (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ is_swap_pmd (int /*<<< orphan*/ ) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pmd_devmap (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none_or_trans_huge_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ zap_huge_pmd (struct mmu_gather*,struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long zap_pte_range (struct mmu_gather*,struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,struct zap_details*) ; 

__attribute__((used)) static inline unsigned long zap_pmd_range(struct mmu_gather *tlb,
				struct vm_area_struct *vma, pud_t *pud,
				unsigned long addr, unsigned long end,
				struct zap_details *details)
{
	pmd_t *pmd;
	unsigned long next;

	pmd = pmd_offset(pud, addr);
	do {
		next = pmd_addr_end(addr, end);
		if (is_swap_pmd(*pmd) || pmd_trans_huge(*pmd) || pmd_devmap(*pmd)) {
			if (next - addr != HPAGE_PMD_SIZE)
				__split_huge_pmd(vma, pmd, addr, false, NULL);
			else if (zap_huge_pmd(tlb, vma, pmd, addr))
				goto next;
			/* fall through */
		}
		/*
		 * Here there can be other concurrent MADV_DONTNEED or
		 * trans huge page faults running, and if the pmd is
		 * none or trans huge it can change under us. This is
		 * because MADV_DONTNEED holds the mmap_sem in read
		 * mode.
		 */
		if (pmd_none_or_trans_huge_or_clear_bad(pmd))
			goto next;
		next = zap_pte_range(tlb, vma, pmd, addr, next, details);
next:
		cond_resched();
	} while (pmd++, addr = next, addr != end);

	return addr;
}