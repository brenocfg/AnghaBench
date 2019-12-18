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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_thp_or_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stage2_get_pud (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stage2_pmd_offset (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stage2_pud_huge (struct kvm*,int /*<<< orphan*/ ) ; 
 scalar_t__ stage2_pud_none (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage2_pud_present (struct kvm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool stage2_get_leaf_entry(struct kvm *kvm, phys_addr_t addr,
				  pud_t **pudpp, pmd_t **pmdpp, pte_t **ptepp)
{
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	*pudpp = NULL;
	*pmdpp = NULL;
	*ptepp = NULL;

	pudp = stage2_get_pud(kvm, NULL, addr);
	if (!pudp || stage2_pud_none(kvm, *pudp) || !stage2_pud_present(kvm, *pudp))
		return false;

	if (stage2_pud_huge(kvm, *pudp)) {
		*pudpp = pudp;
		return true;
	}

	pmdp = stage2_pmd_offset(kvm, pudp, addr);
	if (!pmdp || pmd_none(*pmdp) || !pmd_present(*pmdp))
		return false;

	if (pmd_thp_or_huge(*pmdp)) {
		*pmdpp = pmdp;
		return true;
	}

	ptep = pte_offset_kernel(pmdp, addr);
	if (!ptep || pte_none(*ptep) || !pte_present(*ptep))
		return false;

	*ptepp = ptep;
	return true;
}