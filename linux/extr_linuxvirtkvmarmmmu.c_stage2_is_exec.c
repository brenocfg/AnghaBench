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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int kvm_s2pmd_exec (int /*<<< orphan*/ *) ; 
 int kvm_s2pte_exec (int /*<<< orphan*/ *) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_thp_or_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stage2_get_pmd (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool stage2_is_exec(struct kvm *kvm, phys_addr_t addr)
{
	pmd_t *pmdp;
	pte_t *ptep;

	pmdp = stage2_get_pmd(kvm, NULL, addr);
	if (!pmdp || pmd_none(*pmdp) || !pmd_present(*pmdp))
		return false;

	if (pmd_thp_or_huge(*pmdp))
		return kvm_s2pmd_exec(pmdp);

	ptep = pte_offset_kernel(pmdp, addr);
	if (!ptep || pte_none(*ptep) || !pte_present(*ptep))
		return false;

	return kvm_s2pte_exec(ptep);
}