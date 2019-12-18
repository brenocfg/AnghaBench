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
struct kvm_memory_slot {scalar_t__ dirty_bitmap; scalar_t__ npages; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_arch_free_memslot (struct kvm*,struct kvm_memory_slot*,struct kvm_memory_slot*) ; 
 int /*<<< orphan*/  kvm_destroy_dirty_bitmap (struct kvm_memory_slot*) ; 

__attribute__((used)) static void kvm_free_memslot(struct kvm *kvm, struct kvm_memory_slot *free,
			      struct kvm_memory_slot *dont)
{
	if (!dont || free->dirty_bitmap != dont->dirty_bitmap)
		kvm_destroy_dirty_bitmap(free);

	kvm_arch_free_memslot(kvm, free, dont);

	free->npages = 0;
}