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
 int /*<<< orphan*/  kvm_s2pte_readonly (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_set_s2pte_readonly (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void stage2_wp_ptes(pmd_t *pmd, phys_addr_t addr, phys_addr_t end)
{
	pte_t *pte;

	pte = pte_offset_kernel(pmd, addr);
	do {
		if (!pte_none(*pte)) {
			if (!kvm_s2pte_readonly(pte))
				kvm_set_s2pte_readonly(pte);
		}
	} while (pte++, addr += PAGE_SIZE, addr != end);
}