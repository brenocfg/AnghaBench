#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  if_broot; } ;
struct TYPE_5__ {scalar_t__ di_format; scalar_t__ di_nextents; } ;
struct xfs_inode {TYPE_3__ i_df; TYPE_2__ i_d; TYPE_1__* i_mount; } ;
struct TYPE_4__ {int /*<<< orphan*/  m_sb; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ XFS_BMAP_BMDR_SPACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_DINODE_FMT_BTREE ; 
 scalar_t__ XFS_DINODE_FMT_EXTENTS ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 scalar_t__ XFS_IFORK_BOFF (struct xfs_inode*) ; 
 scalar_t__ XFS_IFORK_MAXEXT (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_IFORK_NEXTENTS (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_IFORK_Q (struct xfs_inode*) ; 
 scalar_t__ xfs_sb_version_hasrmapbt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xfs_swap_extents_check_format(
	struct xfs_inode	*ip,	/* target inode */
	struct xfs_inode	*tip)	/* tmp inode */
{

	/* Should never get a local format */
	if (ip->i_d.di_format == XFS_DINODE_FMT_LOCAL ||
	    tip->i_d.di_format == XFS_DINODE_FMT_LOCAL)
		return -EINVAL;

	/*
	 * if the target inode has less extents that then temporary inode then
	 * why did userspace call us?
	 */
	if (ip->i_d.di_nextents < tip->i_d.di_nextents)
		return -EINVAL;

	/*
	 * If we have to use the (expensive) rmap swap method, we can
	 * handle any number of extents and any format.
	 */
	if (xfs_sb_version_hasrmapbt(&ip->i_mount->m_sb))
		return 0;

	/*
	 * if the target inode is in extent form and the temp inode is in btree
	 * form then we will end up with the target inode in the wrong format
	 * as we already know there are less extents in the temp inode.
	 */
	if (ip->i_d.di_format == XFS_DINODE_FMT_EXTENTS &&
	    tip->i_d.di_format == XFS_DINODE_FMT_BTREE)
		return -EINVAL;

	/* Check temp in extent form to max in target */
	if (tip->i_d.di_format == XFS_DINODE_FMT_EXTENTS &&
	    XFS_IFORK_NEXTENTS(tip, XFS_DATA_FORK) >
			XFS_IFORK_MAXEXT(ip, XFS_DATA_FORK))
		return -EINVAL;

	/* Check target in extent form to max in temp */
	if (ip->i_d.di_format == XFS_DINODE_FMT_EXTENTS &&
	    XFS_IFORK_NEXTENTS(ip, XFS_DATA_FORK) >
			XFS_IFORK_MAXEXT(tip, XFS_DATA_FORK))
		return -EINVAL;

	/*
	 * If we are in a btree format, check that the temp root block will fit
	 * in the target and that it has enough extents to be in btree format
	 * in the target.
	 *
	 * Note that we have to be careful to allow btree->extent conversions
	 * (a common defrag case) which will occur when the temp inode is in
	 * extent format...
	 */
	if (tip->i_d.di_format == XFS_DINODE_FMT_BTREE) {
		if (XFS_IFORK_Q(ip) &&
		    XFS_BMAP_BMDR_SPACE(tip->i_df.if_broot) > XFS_IFORK_BOFF(ip))
			return -EINVAL;
		if (XFS_IFORK_NEXTENTS(tip, XFS_DATA_FORK) <=
		    XFS_IFORK_MAXEXT(ip, XFS_DATA_FORK))
			return -EINVAL;
	}

	/* Reciprocal target->temp btree format checks */
	if (ip->i_d.di_format == XFS_DINODE_FMT_BTREE) {
		if (XFS_IFORK_Q(tip) &&
		    XFS_BMAP_BMDR_SPACE(ip->i_df.if_broot) > XFS_IFORK_BOFF(tip))
			return -EINVAL;
		if (XFS_IFORK_NEXTENTS(ip, XFS_DATA_FORK) <=
		    XFS_IFORK_MAXEXT(tip, XFS_DATA_FORK))
			return -EINVAL;
	}

	return 0;
}