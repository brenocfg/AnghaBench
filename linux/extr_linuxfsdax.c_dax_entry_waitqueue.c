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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct exceptional_entry_key {unsigned long entry_start; struct address_space* mapping; } ;
struct address_space {int dummy; } ;
typedef  unsigned long pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  DAX_WAIT_TABLE_BITS ; 
 unsigned long PG_PMD_COLOUR ; 
 scalar_t__ dax_is_pmd_entry (void*) ; 
 unsigned long hash_long (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wait_table ; 

__attribute__((used)) static wait_queue_head_t *dax_entry_waitqueue(struct address_space *mapping,
		pgoff_t index, void *entry, struct exceptional_entry_key *key)
{
	unsigned long hash;

	/*
	 * If 'entry' is a PMD, align the 'index' that we use for the wait
	 * queue to the start of that PMD.  This ensures that all offsets in
	 * the range covered by the PMD map to the same bit lock.
	 */
	if (dax_is_pmd_entry(entry))
		index &= ~PG_PMD_COLOUR;

	key->mapping = mapping;
	key->entry_start = index;

	hash = hash_long((unsigned long)mapping ^ index, DAX_WAIT_TABLE_BITS);
	return wait_table + hash;
}