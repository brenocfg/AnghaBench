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
struct kvm_memory_slot {int flags; scalar_t__ dirty_bitmap; } ;

/* Variables and functions */
 int KVM_MEM_READONLY ; 

__attribute__((used)) static bool memslot_is_logging(struct kvm_memory_slot *memslot)
{
	return memslot->dirty_bitmap && !(memslot->flags & KVM_MEM_READONLY);
}