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
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_tlb_flush_vmid_ipa (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_thp_or_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stage2_dissolve_pmd(struct kvm *kvm, phys_addr_t addr, pmd_t *pmd)
{
	if (!pmd_thp_or_huge(*pmd))
		return;

	pmd_clear(pmd);
	kvm_tlb_flush_vmid_ipa(kvm, addr);
	put_page(virt_to_page(pmd));
}