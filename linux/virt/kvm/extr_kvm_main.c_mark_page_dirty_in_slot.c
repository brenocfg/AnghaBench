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
struct kvm_memory_slot {unsigned long base_gfn; scalar_t__ dirty_bitmap; } ;
typedef  unsigned long gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit_le (unsigned long,scalar_t__) ; 

__attribute__((used)) static void mark_page_dirty_in_slot(struct kvm_memory_slot *memslot,
				    gfn_t gfn)
{
	if (memslot && memslot->dirty_bitmap) {
		unsigned long rel_gfn = gfn - memslot->base_gfn;

		set_bit_le(rel_gfn, memslot->dirty_bitmap);
	}
}