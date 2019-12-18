#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zap_details {int dummy; } ;
struct vm_area_struct {int dummy; } ;
struct mmu_gather {TYPE_1__* mm; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  p4d_t ;
struct TYPE_2__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 unsigned long HPAGE_PUD_SIZE ; 
 int /*<<< orphan*/  VM_BUG_ON_VMA (int,struct vm_area_struct*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long pud_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pud_devmap (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  split_huge_pud (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ zap_huge_pud (struct mmu_gather*,struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long zap_pmd_range (struct mmu_gather*,struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,struct zap_details*) ; 

__attribute__((used)) static inline unsigned long zap_pud_range(struct mmu_gather *tlb,
				struct vm_area_struct *vma, p4d_t *p4d,
				unsigned long addr, unsigned long end,
				struct zap_details *details)
{
	pud_t *pud;
	unsigned long next;

	pud = pud_offset(p4d, addr);
	do {
		next = pud_addr_end(addr, end);
		if (pud_trans_huge(*pud) || pud_devmap(*pud)) {
			if (next - addr != HPAGE_PUD_SIZE) {
				VM_BUG_ON_VMA(!rwsem_is_locked(&tlb->mm->mmap_sem), vma);
				split_huge_pud(vma, pud, addr);
			} else if (zap_huge_pud(tlb, vma, pud, addr))
				goto next;
			/* fall through */
		}
		if (pud_none_or_clear_bad(pud))
			continue;
		next = zap_pmd_range(tlb, vma, pud, addr, next, details);
next:
		cond_resched();
	} while (pud++, addr = next, addr != end);

	return addr;
}