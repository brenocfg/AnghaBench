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
 int /*<<< orphan*/  __clear_shadow_entry (struct address_space*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_shadow_entry(struct address_space *mapping, pgoff_t index,
			       void *entry)
{
	xa_lock_irq(&mapping->i_pages);
	__clear_shadow_entry(mapping, index, entry);
	xa_unlock_irq(&mapping->i_pages);
}