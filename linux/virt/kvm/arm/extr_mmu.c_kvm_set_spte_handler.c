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
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  stage2_set_pte (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_set_spte_handler(struct kvm *kvm, gpa_t gpa, u64 size, void *data)
{
	pte_t *pte = (pte_t *)data;

	WARN_ON(size != PAGE_SIZE);
	/*
	 * We can always call stage2_set_pte with KVM_S2PTE_FLAG_LOGGING_ACTIVE
	 * flag clear because MMU notifiers will have unmapped a huge PMD before
	 * calling ->change_pte() (which in turn calls kvm_set_spte_hva()) and
	 * therefore stage2_set_pte() never needs to clear out a huge PMD
	 * through this calling path.
	 */
	stage2_set_pte(kvm, NULL, gpa, pte, 0);
	return 0;
}