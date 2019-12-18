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
struct kvm_memory_slot {int /*<<< orphan*/  dirty_bitmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int kvm_dirty_bitmap_bytes (struct kvm_memory_slot*) ; 
 int /*<<< orphan*/  kvzalloc (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_create_dirty_bitmap(struct kvm_memory_slot *memslot)
{
	unsigned long dirty_bytes = 2 * kvm_dirty_bitmap_bytes(memslot);

	memslot->dirty_bitmap = kvzalloc(dirty_bytes, GFP_KERNEL_ACCOUNT);
	if (!memslot->dirty_bitmap)
		return -ENOMEM;

	return 0;
}