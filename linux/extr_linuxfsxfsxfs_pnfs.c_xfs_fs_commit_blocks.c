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
typedef  scalar_t__ u64 ;
struct xfs_trans {int dummy; } ;
struct xfs_mount {int dummy; } ;
struct TYPE_3__ {scalar_t__ di_size; } ;
struct xfs_inode {TYPE_1__ i_d; struct xfs_mount* i_mount; } ;
struct iomap {scalar_t__ offset; scalar_t__ length; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct iattr {int ia_valid; scalar_t__ ia_size; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  tr_ichange; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ATTR_ATIME ; 
 int ATTR_CTIME ; 
 int ATTR_MTIME ; 
 int ATTR_SIZE ; 
 TYPE_2__* M_RES (struct xfs_mount*) ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct xfs_inode* XFS_I (struct inode*) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int /*<<< orphan*/  XFS_IOLOCK_EXCL ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int invalidate_inode_pages2_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_iomap_write_unwritten (struct xfs_inode*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_pnfs_validate_isize (struct xfs_inode*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_setattr_time (struct xfs_inode*,struct iattr*) ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (struct xfs_trans*) ; 

int
xfs_fs_commit_blocks(
	struct inode		*inode,
	struct iomap		*maps,
	int			nr_maps,
	struct iattr		*iattr)
{
	struct xfs_inode	*ip = XFS_I(inode);
	struct xfs_mount	*mp = ip->i_mount;
	struct xfs_trans	*tp;
	bool			update_isize = false;
	int			error, i;
	loff_t			size;

	ASSERT(iattr->ia_valid & (ATTR_ATIME|ATTR_CTIME|ATTR_MTIME));

	xfs_ilock(ip, XFS_IOLOCK_EXCL);

	size = i_size_read(inode);
	if ((iattr->ia_valid & ATTR_SIZE) && iattr->ia_size > size) {
		update_isize = true;
		size = iattr->ia_size;
	}

	for (i = 0; i < nr_maps; i++) {
		u64 start, length, end;

		start = maps[i].offset;
		if (start > size)
			continue;

		end = start + maps[i].length;
		if (end > size)
			end = size;

		length = end - start;
		if (!length)
			continue;
	
		/*
		 * Make sure reads through the pagecache see the new data.
		 */
		error = invalidate_inode_pages2_range(inode->i_mapping,
					start >> PAGE_SHIFT,
					(end - 1) >> PAGE_SHIFT);
		WARN_ON_ONCE(error);

		error = xfs_iomap_write_unwritten(ip, start, length, false);
		if (error)
			goto out_drop_iolock;
	}

	if (update_isize) {
		error = xfs_pnfs_validate_isize(ip, size);
		if (error)
			goto out_drop_iolock;
	}

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ichange, 0, 0, 0, &tp);
	if (error)
		goto out_drop_iolock;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

	xfs_setattr_time(ip, iattr);
	if (update_isize) {
		i_size_write(inode, iattr->ia_size);
		ip->i_d.di_size = iattr->ia_size;
	}

	xfs_trans_set_sync(tp);
	error = xfs_trans_commit(tp);

out_drop_iolock:
	xfs_iunlock(ip, XFS_IOLOCK_EXCL);
	return error;
}