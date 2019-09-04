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
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
typedef  int /*<<< orphan*/  xfs_filblks_t ;
typedef  scalar_t__ xfs_extlen_t ;
typedef  scalar_t__ u64 ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct TYPE_2__ {int di_flags2; scalar_t__ di_cowextsize; } ;
struct xfs_inode {TYPE_1__ i_d; struct xfs_mount* i_mount; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  XFS_B_TO_FSB (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  XFS_B_TO_FSBT (struct xfs_mount*,scalar_t__) ; 
 int XFS_DIFLAG2_COWEXTSIZE ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 struct xfs_inode* XFS_I (struct inode*) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 struct inode* file_inode (struct file*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  trace_xfs_reflink_remap_range (struct xfs_inode*,scalar_t__,scalar_t__,struct xfs_inode*,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_reflink_remap_range_error (struct xfs_inode*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_reflink_remap_blocks (struct xfs_inode*,int /*<<< orphan*/ ,struct xfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ xfs_reflink_remap_prep (struct file*,scalar_t__,struct file*,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  xfs_reflink_remap_unlock (struct file*,struct file*) ; 
 scalar_t__ xfs_reflink_update_dest (struct xfs_inode*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  xfs_sb_version_hasreflink (int /*<<< orphan*/ *) ; 

int
xfs_reflink_remap_range(
	struct file		*file_in,
	loff_t			pos_in,
	struct file		*file_out,
	loff_t			pos_out,
	u64			len,
	bool			is_dedupe)
{
	struct inode		*inode_in = file_inode(file_in);
	struct xfs_inode	*src = XFS_I(inode_in);
	struct inode		*inode_out = file_inode(file_out);
	struct xfs_inode	*dest = XFS_I(inode_out);
	struct xfs_mount	*mp = src->i_mount;
	xfs_fileoff_t		sfsbno, dfsbno;
	xfs_filblks_t		fsblen;
	xfs_extlen_t		cowextsize;
	ssize_t			ret;

	if (!xfs_sb_version_hasreflink(&mp->m_sb))
		return -EOPNOTSUPP;

	if (XFS_FORCED_SHUTDOWN(mp))
		return -EIO;

	/* Prepare and then clone file data. */
	ret = xfs_reflink_remap_prep(file_in, pos_in, file_out, pos_out,
			&len, is_dedupe);
	if (ret <= 0)
		return ret;

	trace_xfs_reflink_remap_range(src, pos_in, len, dest, pos_out);

	dfsbno = XFS_B_TO_FSBT(mp, pos_out);
	sfsbno = XFS_B_TO_FSBT(mp, pos_in);
	fsblen = XFS_B_TO_FSB(mp, len);
	ret = xfs_reflink_remap_blocks(src, sfsbno, dest, dfsbno, fsblen,
			pos_out + len);
	if (ret)
		goto out_unlock;

	/*
	 * Carry the cowextsize hint from src to dest if we're sharing the
	 * entire source file to the entire destination file, the source file
	 * has a cowextsize hint, and the destination file does not.
	 */
	cowextsize = 0;
	if (pos_in == 0 && len == i_size_read(inode_in) &&
	    (src->i_d.di_flags2 & XFS_DIFLAG2_COWEXTSIZE) &&
	    pos_out == 0 && len >= i_size_read(inode_out) &&
	    !(dest->i_d.di_flags2 & XFS_DIFLAG2_COWEXTSIZE))
		cowextsize = src->i_d.di_cowextsize;

	ret = xfs_reflink_update_dest(dest, pos_out + len, cowextsize,
			is_dedupe);

out_unlock:
	xfs_reflink_remap_unlock(file_in, file_out);
	if (ret)
		trace_xfs_reflink_remap_range_error(dest, ret, _RET_IP_);
	return ret;
}