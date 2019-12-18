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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  kvm_pfn_t ;
struct TYPE_2__ {int /*<<< orphan*/  mmu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_pud_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s2pud_mkyoung (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_pfn_accessed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkyoung (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkyoung (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stage2_get_leaf_entry (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  trace_kvm_access_fault (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_access_fault(struct kvm_vcpu *vcpu, phys_addr_t fault_ipa)
{
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	kvm_pfn_t pfn;
	bool pfn_valid = false;

	trace_kvm_access_fault(fault_ipa);

	spin_lock(&vcpu->kvm->mmu_lock);

	if (!stage2_get_leaf_entry(vcpu->kvm, fault_ipa, &pud, &pmd, &pte))
		goto out;

	if (pud) {		/* HugeTLB */
		*pud = kvm_s2pud_mkyoung(*pud);
		pfn = kvm_pud_pfn(*pud);
		pfn_valid = true;
	} else	if (pmd) {	/* THP, HugeTLB */
		*pmd = pmd_mkyoung(*pmd);
		pfn = pmd_pfn(*pmd);
		pfn_valid = true;
	} else {
		*pte = pte_mkyoung(*pte);	/* Just a page... */
		pfn = pte_pfn(*pte);
		pfn_valid = true;
	}

out:
	spin_unlock(&vcpu->kvm->mmu_lock);
	if (pfn_valid)
		kvm_set_pfn_accessed(pfn);
}