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

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfs_uuid_table ; 
 scalar_t__ xfs_uuid_table_size ; 

void
xfs_uuid_table_free(void)
{
	if (xfs_uuid_table_size == 0)
		return;
	kmem_free(xfs_uuid_table);
	xfs_uuid_table = NULL;
	xfs_uuid_table_size = 0;
}