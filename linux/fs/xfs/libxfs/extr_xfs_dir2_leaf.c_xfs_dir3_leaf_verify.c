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
typedef  scalar_t__ xfs_failaddr_t ;
struct xfs_mount {int dummy; } ;
struct xfs_dir2_leaf {int dummy; } ;
struct xfs_buf {struct xfs_dir2_leaf* b_addr; struct xfs_mount* b_mount; } ;

/* Variables and functions */
 scalar_t__ xfs_da3_blkinfo_verify (struct xfs_buf*,struct xfs_dir2_leaf*) ; 
 scalar_t__ xfs_dir3_leaf_check_int (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct xfs_dir2_leaf*) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_dir3_leaf_verify(
	struct xfs_buf		*bp)
{
	struct xfs_mount	*mp = bp->b_mount;
	struct xfs_dir2_leaf	*leaf = bp->b_addr;
	xfs_failaddr_t		fa;

	fa = xfs_da3_blkinfo_verify(bp, bp->b_addr);
	if (fa)
		return fa;

	return xfs_dir3_leaf_check_int(mp, NULL, NULL, leaf);
}