#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_fileoff_t ;
struct xfs_mount {TYPE_1__* m_super; } ;
struct TYPE_4__ {int if_flags; } ;
struct xfs_inode {TYPE_2__* i_cowfp; TYPE_2__ i_df; struct xfs_mount* i_mount; } ;
struct xfs_iext_cursor {int dummy; } ;
struct xfs_bmbt_irec {scalar_t__ br_startoff; scalar_t__ br_blockcount; int /*<<< orphan*/  br_state; int /*<<< orphan*/  br_startblock; } ;
struct iomap {int /*<<< orphan*/  type; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_3__ {scalar_t__ s_maxbytes; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HOLESTARTBLOCK ; 
 int /*<<< orphan*/  IOMAP_UNWRITTEN ; 
 scalar_t__ NULLFILEOFF ; 
 scalar_t__ XFS_B_TO_FSB (struct xfs_mount*,scalar_t__) ; 
 scalar_t__ XFS_B_TO_FSBT (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int /*<<< orphan*/  XFS_EXT_NORM ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 struct xfs_inode* XFS_I (struct inode*) ; 
 int XFS_IFEXTENTS ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int xfs_bmbt_to_iomap (struct xfs_inode*,struct iomap*,struct xfs_bmbt_irec*,int) ; 
 scalar_t__ xfs_iext_lookup_extent (struct xfs_inode*,TYPE_2__*,scalar_t__,struct xfs_iext_cursor*,struct xfs_bmbt_irec*) ; 
 unsigned int xfs_ilock_data_map_shared (struct xfs_inode*) ; 
 scalar_t__ xfs_inode_has_cow_data (struct xfs_inode*) ; 
 int xfs_iread_extents (int /*<<< orphan*/ *,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,unsigned int) ; 
 int /*<<< orphan*/  xfs_trim_extent (struct xfs_bmbt_irec*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
xfs_seek_iomap_begin(
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
	xfs_fileoff_t		cow_fsb = NULLFILEOFF, data_fsb = NULLFILEOFF;
	struct xfs_iext_cursor	icur;
	struct xfs_bmbt_irec	imap, cmap;
	int			error = 0;
	unsigned		lockmode;

	if (XFS_FORCED_SHUTDOWN(mp))
		return -EIO;

	lockmode = xfs_ilock_data_map_shared(ip);
	if (!(ip->i_df.if_flags & XFS_IFEXTENTS)) {
		error = xfs_iread_extents(NULL, ip, XFS_DATA_FORK);
		if (error)
			goto out_unlock;
	}

	if (xfs_iext_lookup_extent(ip, &ip->i_df, offset_fsb, &icur, &imap)) {
		/*
		 * If we found a data extent we are done.
		 */
		if (imap.br_startoff <= offset_fsb)
			goto done;
		data_fsb = imap.br_startoff;
	} else {
		/*
		 * Fake a hole until the end of the file.
		 */
		data_fsb = min(XFS_B_TO_FSB(mp, offset + length),
			       XFS_B_TO_FSB(mp, mp->m_super->s_maxbytes));
	}

	/*
	 * If a COW fork extent covers the hole, report it - capped to the next
	 * data fork extent:
	 */
	if (xfs_inode_has_cow_data(ip) &&
	    xfs_iext_lookup_extent(ip, ip->i_cowfp, offset_fsb, &icur, &cmap))
		cow_fsb = cmap.br_startoff;
	if (cow_fsb != NULLFILEOFF && cow_fsb <= offset_fsb) {
		if (data_fsb < cow_fsb + cmap.br_blockcount)
			end_fsb = min(end_fsb, data_fsb);
		xfs_trim_extent(&cmap, offset_fsb, end_fsb);
		error = xfs_bmbt_to_iomap(ip, iomap, &cmap, true);
		/*
		 * This is a COW extent, so we must probe the page cache
		 * because there could be dirty page cache being backed
		 * by this extent.
		 */
		iomap->type = IOMAP_UNWRITTEN;
		goto out_unlock;
	}

	/*
	 * Else report a hole, capped to the next found data or COW extent.
	 */
	if (cow_fsb != NULLFILEOFF && cow_fsb < data_fsb)
		imap.br_blockcount = cow_fsb - offset_fsb;
	else
		imap.br_blockcount = data_fsb - offset_fsb;
	imap.br_startoff = offset_fsb;
	imap.br_startblock = HOLESTARTBLOCK;
	imap.br_state = XFS_EXT_NORM;
done:
	xfs_trim_extent(&imap, offset_fsb, end_fsb);
	error = xfs_bmbt_to_iomap(ip, iomap, &imap, false);
out_unlock:
	xfs_iunlock(ip, lockmode);
	return error;
}