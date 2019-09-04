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
struct address_space {unsigned long nrpages; unsigned long nrexceptional; int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  mapping_set_exiting (struct address_space*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  truncate_inode_pages (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

void truncate_inode_pages_final(struct address_space *mapping)
{
	unsigned long nrexceptional;
	unsigned long nrpages;

	/*
	 * Page reclaim can not participate in regular inode lifetime
	 * management (can't call iput()) and thus can race with the
	 * inode teardown.  Tell it when the address space is exiting,
	 * so that it does not install eviction information after the
	 * final truncate has begun.
	 */
	mapping_set_exiting(mapping);

	/*
	 * When reclaim installs eviction entries, it increases
	 * nrexceptional first, then decreases nrpages.  Make sure we see
	 * this in the right order or we might miss an entry.
	 */
	nrpages = mapping->nrpages;
	smp_rmb();
	nrexceptional = mapping->nrexceptional;

	if (nrpages || nrexceptional) {
		/*
		 * As truncation uses a lockless tree lookup, cycle
		 * the tree lock to make sure any ongoing tree
		 * modification that does not see AS_EXITING is
		 * completed before starting the final truncate.
		 */
		xa_lock_irq(&mapping->i_pages);
		xa_unlock_irq(&mapping->i_pages);
	}

	/*
	 * Cleancache needs notification even if there are no pages or shadow
	 * entries.
	 */
	truncate_inode_pages(mapping, 0);
}