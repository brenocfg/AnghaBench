#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfs_trans {int dummy; } ;
struct xfs_mount {TYPE_1__* m_dir_geo; } ;
struct xfs_inode {struct xfs_mount* i_mount; } ;
struct xfs_buf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  datablk; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BLFT_DIR_BLOCK_BUF ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int xfs_da_read_buf (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ,int,struct xfs_buf**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_dir3_block_buf_ops ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ) ; 

int
xfs_dir3_block_read(
	struct xfs_trans	*tp,
	struct xfs_inode	*dp,
	struct xfs_buf		**bpp)
{
	struct xfs_mount	*mp = dp->i_mount;
	int			err;

	err = xfs_da_read_buf(tp, dp, mp->m_dir_geo->datablk, -1, bpp,
				XFS_DATA_FORK, &xfs_dir3_block_buf_ops);
	if (!err && tp && *bpp)
		xfs_trans_buf_set_type(tp, *bpp, XFS_BLFT_DIR_BLOCK_BUF);
	return err;
}