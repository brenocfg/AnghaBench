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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_hyp_pmd_entry (int /*<<< orphan*/ *) ; 
 scalar_t__ hyp_pte_table_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unmap_hyp_ptes(pmd_t *pmd, phys_addr_t addr, phys_addr_t end)
{
	pte_t *pte, *start_pte;

	start_pte = pte = pte_offset_kernel(pmd, addr);
	do {
		if (!pte_none(*pte)) {
			kvm_set_pte(pte, __pte(0));
			put_page(virt_to_page(pte));
		}
	} while (pte++, addr += PAGE_SIZE, addr != end);

	if (hyp_pte_table_empty(start_pte))
		clear_hyp_pmd_entry(pmd);
}