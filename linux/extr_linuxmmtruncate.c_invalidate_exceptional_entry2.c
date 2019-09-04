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
 int /*<<< orphan*/  clear_shadow_entry (struct address_space*,int /*<<< orphan*/ ,void*) ; 
 int dax_invalidate_mapping_entry_sync (struct address_space*,int /*<<< orphan*/ ) ; 
 scalar_t__ dax_mapping (struct address_space*) ; 
 scalar_t__ shmem_mapping (struct address_space*) ; 

__attribute__((used)) static int invalidate_exceptional_entry2(struct address_space *mapping,
					 pgoff_t index, void *entry)
{
	/* Handled by shmem itself */
	if (shmem_mapping(mapping))
		return 1;
	if (dax_mapping(mapping))
		return dax_invalidate_mapping_entry_sync(mapping, index);
	clear_shadow_entry(mapping, index, entry);
	return 1;
}