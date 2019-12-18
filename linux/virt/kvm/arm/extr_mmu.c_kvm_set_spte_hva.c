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
struct TYPE_2__ {int /*<<< orphan*/  pgd; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  kvm_pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_S2 ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  clean_dcache_guest_page (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  handle_hva_to_gpa (struct kvm*,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_pfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_spte_handler ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_set_spte_hva (unsigned long) ; 

int kvm_set_spte_hva(struct kvm *kvm, unsigned long hva, pte_t pte)
{
	unsigned long end = hva + PAGE_SIZE;
	kvm_pfn_t pfn = pte_pfn(pte);
	pte_t stage2_pte;

	if (!kvm->arch.pgd)
		return 0;

	trace_kvm_set_spte_hva(hva);

	/*
	 * We've moved a page around, probably through CoW, so let's treat it
	 * just like a translation fault and clean the cache to the PoC.
	 */
	clean_dcache_guest_page(pfn, PAGE_SIZE);
	stage2_pte = kvm_pfn_pte(pfn, PAGE_S2);
	handle_hva_to_gpa(kvm, hva, end, &kvm_set_spte_handler, &stage2_pte);

	return 0;
}