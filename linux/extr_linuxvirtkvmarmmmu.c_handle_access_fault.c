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
struct kvm_vcpu {TYPE_1__* kvm; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  kvm_pfn_t ;
struct TYPE_2__ {int /*<<< orphan*/  mmu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_set_pfn_accessed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkyoung (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_thp_or_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkyoung (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stage2_get_pmd (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_access_fault (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_access_fault(struct kvm_vcpu *vcpu, phys_addr_t fault_ipa)
{
	pmd_t *pmd;
	pte_t *pte;
	kvm_pfn_t pfn;
	bool pfn_valid = false;

	trace_kvm_access_fault(fault_ipa);

	spin_lock(&vcpu->kvm->mmu_lock);

	pmd = stage2_get_pmd(vcpu->kvm, NULL, fault_ipa);
	if (!pmd || pmd_none(*pmd))	/* Nothing there */
		goto out;

	if (pmd_thp_or_huge(*pmd)) {	/* THP, HugeTLB */
		*pmd = pmd_mkyoung(*pmd);
		pfn = pmd_pfn(*pmd);
		pfn_valid = true;
		goto out;
	}

	pte = pte_offset_kernel(pmd, fault_ipa);
	if (pte_none(*pte))		/* Nothing there either */
		goto out;

	*pte = pte_mkyoung(*pte);	/* Just a page... */
	pfn = pte_pfn(*pte);
	pfn_valid = true;
out:
	spin_unlock(&vcpu->kvm->mmu_lock);
	if (pfn_valid)
		kvm_set_pfn_accessed(pfn);
}