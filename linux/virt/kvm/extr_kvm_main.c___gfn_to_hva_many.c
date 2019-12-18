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
struct kvm_memory_slot {int flags; scalar_t__ base_gfn; scalar_t__ npages; } ;
typedef  scalar_t__ gfn_t ;

/* Variables and functions */
 unsigned long KVM_HVA_ERR_BAD ; 
 unsigned long KVM_HVA_ERR_RO_BAD ; 
 int KVM_MEMSLOT_INVALID ; 
 unsigned long __gfn_to_hva_memslot (struct kvm_memory_slot*,scalar_t__) ; 
 scalar_t__ memslot_is_readonly (struct kvm_memory_slot*) ; 

__attribute__((used)) static unsigned long __gfn_to_hva_many(struct kvm_memory_slot *slot, gfn_t gfn,
				       gfn_t *nr_pages, bool write)
{
	if (!slot || slot->flags & KVM_MEMSLOT_INVALID)
		return KVM_HVA_ERR_BAD;

	if (memslot_is_readonly(slot) && write)
		return KVM_HVA_ERR_RO_BAD;

	if (nr_pages)
		*nr_pages = slot->npages - (gfn - slot->base_gfn);

	return __gfn_to_hva_memslot(slot, gfn);
}