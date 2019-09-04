#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  xa_lock; } ;
struct address_space {TYPE_1__ i_pages; } ;

/* Variables and functions */
 unsigned long RADIX_DAX_ENTRY_LOCK ; 
 scalar_t__ radix_tree_deref_slot_protected (void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int slot_locked(struct address_space *mapping, void **slot)
{
	unsigned long entry = (unsigned long)
		radix_tree_deref_slot_protected(slot, &mapping->i_pages.xa_lock);
	return entry & RADIX_DAX_ENTRY_LOCK;
}