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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PMD_SIZE ; 
 scalar_t__ PUD_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int kvm_s2pud_young (int /*<<< orphan*/ ) ; 
 int pmd_young (int /*<<< orphan*/ ) ; 
 int pte_young (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage2_get_leaf_entry (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int kvm_test_age_hva_handler(struct kvm *kvm, gpa_t gpa, u64 size, void *data)
{
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	WARN_ON(size != PAGE_SIZE && size != PMD_SIZE && size != PUD_SIZE);
	if (!stage2_get_leaf_entry(kvm, gpa, &pud, &pmd, &pte))
		return 0;

	if (pud)
		return kvm_s2pud_young(*pud);
	else if (pmd)
		return pmd_young(*pmd);
	else
		return pte_young(*pte);
}