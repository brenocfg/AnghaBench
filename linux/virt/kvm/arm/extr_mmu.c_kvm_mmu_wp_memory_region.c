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
struct kvm_memslots {int dummy; } ;
struct kvm_memory_slot {int base_gfn; int npages; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; } ;
typedef  int phys_addr_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 struct kvm_memory_slot* id_to_memslot (struct kvm_memslots*,int) ; 
 int /*<<< orphan*/  kvm_flush_remote_tlbs (struct kvm*) ; 
 struct kvm_memslots* kvm_memslots (struct kvm*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stage2_wp_range (struct kvm*,int,int) ; 

void kvm_mmu_wp_memory_region(struct kvm *kvm, int slot)
{
	struct kvm_memslots *slots = kvm_memslots(kvm);
	struct kvm_memory_slot *memslot = id_to_memslot(slots, slot);
	phys_addr_t start = memslot->base_gfn << PAGE_SHIFT;
	phys_addr_t end = (memslot->base_gfn + memslot->npages) << PAGE_SHIFT;

	spin_lock(&kvm->mmu_lock);
	stage2_wp_range(kvm, start, end);
	spin_unlock(&kvm->mmu_lock);
	kvm_flush_remote_tlbs(kvm);
}