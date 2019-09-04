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
typedef  int xfs_off_t ;
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_daddr_t ;
struct xfs_mount {TYPE_1__* m_super; } ;
struct xfs_inode {struct xfs_mount* i_mount; } ;
typedef  int sector_t ;
struct TYPE_2__ {int s_blocksize_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  VFS_I (struct xfs_inode*) ; 
 int XFS_BB_TO_FSBT (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int blkdev_issue_zeroout (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_find_bdev_for_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_fsb_to_db (struct xfs_inode*,int /*<<< orphan*/ ) ; 

int
xfs_zero_extent(
	struct xfs_inode *ip,
	xfs_fsblock_t	start_fsb,
	xfs_off_t	count_fsb)
{
	struct xfs_mount *mp = ip->i_mount;
	xfs_daddr_t	sector = xfs_fsb_to_db(ip, start_fsb);
	sector_t	block = XFS_BB_TO_FSBT(mp, sector);

	return blkdev_issue_zeroout(xfs_find_bdev_for_inode(VFS_I(ip)),
		block << (mp->m_super->s_blocksize_bits - 9),
		count_fsb << (mp->m_super->s_blocksize_bits - 9),
		GFP_NOFS, 0);
}