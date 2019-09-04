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
 int /*<<< orphan*/  xfs_agfl_free_defer_type ; 
 int /*<<< orphan*/  xfs_defer_init_op_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_extent_free_defer_type ; 

void
xfs_extent_free_init_defer_op(void)
{
	xfs_defer_init_op_type(&xfs_extent_free_defer_type);
	xfs_defer_init_op_type(&xfs_agfl_free_defer_type);
}