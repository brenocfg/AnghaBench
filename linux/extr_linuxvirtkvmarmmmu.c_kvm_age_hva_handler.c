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
typedef  scalar_t__ u64 ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PMD_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_thp_or_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stage2_get_pmd (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stage2_pmdp_test_and_clear_young (int /*<<< orphan*/ *) ; 
 int stage2_ptep_test_and_clear_young (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_age_hva_handler(struct kvm *kvm, gpa_t gpa, u64 size, void *data)
{
	pmd_t *pmd;
	pte_t *pte;

	WARN_ON(size != PAGE_SIZE && size != PMD_SIZE);
	pmd = stage2_get_pmd(kvm, NULL, gpa);
	if (!pmd || pmd_none(*pmd))	/* Nothing there */
		return 0;

	if (pmd_thp_or_huge(*pmd))	/* THP, HugeTLB */
		return stage2_pmdp_test_and_clear_young(pmd);

	pte = pte_offset_kernel(pmd, gpa);
	if (pte_none(*pte))
		return 0;

	return stage2_ptep_test_and_clear_young(pte);
}