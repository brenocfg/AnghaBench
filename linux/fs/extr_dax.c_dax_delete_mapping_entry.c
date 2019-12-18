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
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __dax_invalidate_entry (struct address_space*,int /*<<< orphan*/ ,int) ; 

int dax_delete_mapping_entry(struct address_space *mapping, pgoff_t index)
{
	int ret = __dax_invalidate_entry(mapping, index, true);

	/*
	 * This gets called from truncate / punch_hole path. As such, the caller
	 * must hold locks protecting against concurrent modifications of the
	 * page cache (usually fs-private i_mmap_sem for writing). Since the
	 * caller has seen a DAX entry for this index, we better find it
	 * at that index as well...
	 */
	WARN_ON_ONCE(!ret);
	return ret;
}