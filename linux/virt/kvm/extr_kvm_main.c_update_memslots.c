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
struct kvm_memslots {int* id_to_index; int used_slots; struct kvm_memory_slot* memslots; } ;
struct kvm_memory_slot {int id; scalar_t__ base_gfn; scalar_t__ npages; } ;
typedef  enum kvm_mr_change { ____Placeholder_kvm_mr_change } kvm_mr_change ;

/* Variables and functions */
 int KVM_MEM_SLOTS_NUM ; 
#define  KVM_MR_CREATE 129 
#define  KVM_MR_DELETE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static void update_memslots(struct kvm_memslots *slots,
			    struct kvm_memory_slot *new,
			    enum kvm_mr_change change)
{
	int id = new->id;
	int i = slots->id_to_index[id];
	struct kvm_memory_slot *mslots = slots->memslots;

	WARN_ON(mslots[i].id != id);
	switch (change) {
	case KVM_MR_CREATE:
		slots->used_slots++;
		WARN_ON(mslots[i].npages || !new->npages);
		break;
	case KVM_MR_DELETE:
		slots->used_slots--;
		WARN_ON(new->npages || !mslots[i].npages);
		break;
	default:
		break;
	}

	while (i < KVM_MEM_SLOTS_NUM - 1 &&
	       new->base_gfn <= mslots[i + 1].base_gfn) {
		if (!mslots[i + 1].npages)
			break;
		mslots[i] = mslots[i + 1];
		slots->id_to_index[mslots[i].id] = i;
		i++;
	}

	/*
	 * The ">=" is needed when creating a slot with base_gfn == 0,
	 * so that it moves before all those with base_gfn == npages == 0.
	 *
	 * On the other hand, if new->npages is zero, the above loop has
	 * already left i pointing to the beginning of the empty part of
	 * mslots, and the ">=" would move the hole backwards in this
	 * case---which is wrong.  So skip the loop when deleting a slot.
	 */
	if (new->npages) {
		while (i > 0 &&
		       new->base_gfn >= mslots[i - 1].base_gfn) {
			mslots[i] = mslots[i - 1];
			slots->id_to_index[mslots[i].id] = i;
			i--;
		}
	} else
		WARN_ON_ONCE(i != slots->used_slots);

	mslots[i] = *new;
	slots->id_to_index[mslots[i].id] = i;
}