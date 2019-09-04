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
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  dax_wake_mapping_entry_waiter (struct address_space*,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void put_unlocked_mapping_entry(struct address_space *mapping,
				       pgoff_t index, void *entry)
{
	if (!entry)
		return;

	/* We have to wake up next waiter for the radix tree entry lock */
	dax_wake_mapping_entry_waiter(mapping, index, entry, false);
}