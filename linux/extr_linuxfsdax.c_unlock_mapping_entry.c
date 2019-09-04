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
struct address_space {int /*<<< orphan*/  i_pages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 void* __radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void***) ; 
 int /*<<< orphan*/  dax_wake_mapping_entry_waiter (struct address_space*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  radix_tree_exceptional_entry (void*) ; 
 int /*<<< orphan*/  slot_locked (struct address_space*,void**) ; 
 int /*<<< orphan*/  unlock_slot (struct address_space*,void**) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unlock_mapping_entry(struct address_space *mapping, pgoff_t index)
{
	void *entry, **slot;

	xa_lock_irq(&mapping->i_pages);
	entry = __radix_tree_lookup(&mapping->i_pages, index, NULL, &slot);
	if (WARN_ON_ONCE(!entry || !radix_tree_exceptional_entry(entry) ||
			 !slot_locked(mapping, slot))) {
		xa_unlock_irq(&mapping->i_pages);
		return;
	}
	unlock_slot(mapping, slot);
	xa_unlock_irq(&mapping->i_pages);
	dax_wake_mapping_entry_waiter(mapping, index, entry, false);
}