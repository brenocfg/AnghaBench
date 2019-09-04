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
typedef  int u64 ;
struct kvm_memslots {int generation; } ;
struct kvm {int /*<<< orphan*/  srcu; int /*<<< orphan*/ * memslots; } ;

/* Variables and functions */
 int KVM_ADDRESS_SPACE_NUM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct kvm_memslots* __kvm_memslots (struct kvm*,int) ; 
 int /*<<< orphan*/  kvm_arch_memslots_updated (struct kvm*,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct kvm_memslots*) ; 
 int /*<<< orphan*/  synchronize_srcu_expedited (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct kvm_memslots *install_new_memslots(struct kvm *kvm,
		int as_id, struct kvm_memslots *slots)
{
	struct kvm_memslots *old_memslots = __kvm_memslots(kvm, as_id);
	u64 gen;

	/*
	 * Set the low bit in the generation, which disables SPTE caching
	 * until the end of synchronize_srcu_expedited.
	 */
	WARN_ON(old_memslots->generation & 1);
	slots->generation = old_memslots->generation + 1;

	rcu_assign_pointer(kvm->memslots[as_id], slots);
	synchronize_srcu_expedited(&kvm->srcu);

	/*
	 * Increment the new memslot generation a second time. This prevents
	 * vm exits that race with memslot updates from caching a memslot
	 * generation that will (potentially) be valid forever.
	 *
	 * Generations must be unique even across address spaces.  We do not need
	 * a global counter for that, instead the generation space is evenly split
	 * across address spaces.  For example, with two address spaces, address
	 * space 0 will use generations 0, 4, 8, ... while * address space 1 will
	 * use generations 2, 6, 10, 14, ...
	 */
	gen = slots->generation + KVM_ADDRESS_SPACE_NUM * 2 - 1;

	kvm_arch_memslots_updated(kvm, gen);

	slots->generation = gen;

	return old_memslots;
}