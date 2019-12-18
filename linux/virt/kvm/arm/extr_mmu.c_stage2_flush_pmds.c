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
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_flush_dcache_pmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_thp_or_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage2_flush_ptes (struct kvm*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ stage2_pmd_addr_end (struct kvm*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * stage2_pmd_offset (struct kvm*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void stage2_flush_pmds(struct kvm *kvm, pud_t *pud,
			      phys_addr_t addr, phys_addr_t end)
{
	pmd_t *pmd;
	phys_addr_t next;

	pmd = stage2_pmd_offset(kvm, pud, addr);
	do {
		next = stage2_pmd_addr_end(kvm, addr, end);
		if (!pmd_none(*pmd)) {
			if (pmd_thp_or_huge(*pmd))
				kvm_flush_dcache_pmd(*pmd);
			else
				stage2_flush_ptes(kvm, pmd, addr, next);
		}
	} while (pmd++, addr = next, addr != end);
}