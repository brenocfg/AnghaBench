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
 int __dax_invalidate_entry (struct address_space*,int /*<<< orphan*/ ,int) ; 

int dax_invalidate_mapping_entry_sync(struct address_space *mapping,
				      pgoff_t index)
{
	return __dax_invalidate_entry(mapping, index, false);
}