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
struct kvm_memory_slot {scalar_t__ id; int flags; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int KVM_MEMSLOT_INVALID ; 
 scalar_t__ KVM_USER_MEM_SLOTS ; 
 struct kvm_memory_slot* gfn_to_memslot (struct kvm*,int /*<<< orphan*/ ) ; 

bool kvm_is_visible_gfn(struct kvm *kvm, gfn_t gfn)
{
	struct kvm_memory_slot *memslot = gfn_to_memslot(kvm, gfn);

	if (!memslot || memslot->id >= KVM_USER_MEM_SLOTS ||
	      memslot->flags & KVM_MEMSLOT_INVALID)
		return false;

	return true;
}