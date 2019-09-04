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
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_inode_t ;
struct xfs_name {int dummy; } ;

/* Variables and functions */
 int xfs_dir_createname (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct xfs_name*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xfs_dir_canenter(
	xfs_trans_t	*tp,
	xfs_inode_t	*dp,
	struct xfs_name	*name)		/* name of entry to add */
{
	return xfs_dir_createname(tp, dp, name, 0, 0);
}