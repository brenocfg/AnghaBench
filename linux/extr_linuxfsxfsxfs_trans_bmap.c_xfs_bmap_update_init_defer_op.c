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
 int /*<<< orphan*/  xfs_bmap_update_defer_type ; 
 int /*<<< orphan*/  xfs_defer_init_op_type (int /*<<< orphan*/ *) ; 

void
xfs_bmap_update_init_defer_op(void)
{
	xfs_defer_init_op_type(&xfs_bmap_update_defer_type);
}