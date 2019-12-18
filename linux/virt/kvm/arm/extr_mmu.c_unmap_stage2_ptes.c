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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_stage2_pmd_entry (struct kvm*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kvm_flush_dcache_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_is_device_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_tlb_flush_vmid_ipa (struct kvm*,scalar_t__) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 scalar_t__ stage2_pte_table_empty (struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unmap_stage2_ptes(struct kvm *kvm, pmd_t *pmd,
		       phys_addr_t addr, phys_addr_t end)
{
	phys_addr_t start_addr = addr;
	pte_t *pte, *start_pte;

	start_pte = pte = pte_offset_kernel(pmd, addr);
	do {
		if (!pte_none(*pte)) {
			pte_t old_pte = *pte;

			kvm_set_pte(pte, __pte(0));
			kvm_tlb_flush_vmid_ipa(kvm, addr);

			/* No need to invalidate the cache for device mappings */
			if (!kvm_is_device_pfn(pte_pfn(old_pte)))
				kvm_flush_dcache_pte(old_pte);

			put_page(virt_to_page(pte));
		}
	} while (pte++, addr += PAGE_SIZE, addr != end);

	if (stage2_pte_table_empty(kvm, start_pte))
		clear_stage2_pmd_entry(kvm, pmd, start_addr);
}