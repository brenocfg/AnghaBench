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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_tlb_flush_vmid_ipa (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage2_pud_clear (struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stage2_pud_huge (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stage2_dissolve_pud(struct kvm *kvm, phys_addr_t addr, pud_t *pudp)
{
	if (!stage2_pud_huge(kvm, *pudp))
		return;

	stage2_pud_clear(kvm, pudp);
	kvm_tlb_flush_vmid_ipa(kvm, addr);
	put_page(virt_to_page(pudp));
}