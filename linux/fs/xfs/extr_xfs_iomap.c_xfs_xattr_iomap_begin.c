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
typedef  scalar_t__ xfs_fileoff_t ;
struct xfs_mount {int dummy; } ;
struct TYPE_2__ {scalar_t__ di_aformat; int /*<<< orphan*/  di_anextents; } ;
struct xfs_inode {TYPE_1__ i_d; struct xfs_mount* i_mount; } ;
struct xfs_bmbt_irec {int dummy; } ;
struct iomap {int dummy; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  XFS_BMAPI_ATTRFORK ; 
 scalar_t__ XFS_B_TO_FSB (struct xfs_mount*,scalar_t__) ; 
 scalar_t__ XFS_B_TO_FSBT (struct xfs_mount*,scalar_t__) ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 struct xfs_inode* XFS_I (struct inode*) ; 
 int /*<<< orphan*/  XFS_IFORK_Q (struct xfs_inode*) ; 
 int xfs_bmapi_read (struct xfs_inode*,scalar_t__,scalar_t__,struct xfs_bmbt_irec*,int*,int /*<<< orphan*/ ) ; 
 int xfs_bmbt_to_iomap (struct xfs_inode*,struct iomap*,struct xfs_bmbt_irec*,int) ; 
 unsigned int xfs_ilock_attr_map_shared (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,unsigned int) ; 

__attribute__((used)) static int
xfs_xattr_iomap_begin(
	struct inode		*inode,
	loff_t			offset,
	loff_t			length,
	unsigned		flags,
	struct iomap		*iomap)
{
	struct xfs_inode	*ip = XFS_I(inode);
	struct xfs_mount	*mp = ip->i_mount;
	xfs_fileoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fileoff_t		end_fsb = XFS_B_TO_FSB(mp, offset + length);
	struct xfs_bmbt_irec	imap;
	int			nimaps = 1, error = 0;
	unsigned		lockmode;

	if (XFS_FORCED_SHUTDOWN(mp))
		return -EIO;

	lockmode = xfs_ilock_attr_map_shared(ip);

	/* if there are no attribute fork or extents, return ENOENT */
	if (!XFS_IFORK_Q(ip) || !ip->i_d.di_anextents) {
		error = -ENOENT;
		goto out_unlock;
	}

	ASSERT(ip->i_d.di_aformat != XFS_DINODE_FMT_LOCAL);
	error = xfs_bmapi_read(ip, offset_fsb, end_fsb - offset_fsb, &imap,
			       &nimaps, XFS_BMAPI_ATTRFORK);
out_unlock:
	xfs_iunlock(ip, lockmode);

	if (error)
		return error;
	ASSERT(nimaps);
	return xfs_bmbt_to_iomap(ip, iomap, &imap, false);
}