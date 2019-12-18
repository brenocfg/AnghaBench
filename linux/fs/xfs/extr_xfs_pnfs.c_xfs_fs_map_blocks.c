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
typedef  scalar_t__ xfs_ufsize_t ;
typedef  scalar_t__ xfs_fileoff_t ;
typedef  int /*<<< orphan*/  uint ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct xfs_mount {int /*<<< orphan*/  m_generation; TYPE_1__* m_super; } ;
struct xfs_inode {struct xfs_mount* i_mount; } ;
struct xfs_bmbt_irec {scalar_t__ br_startblock; } ;
struct iomap {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; TYPE_2__* i_sb; } ;
typedef  scalar_t__ loff_t ;
typedef  enum xfs_prealloc_flags { ____Placeholder_xfs_prealloc_flags } xfs_prealloc_flags ;
struct TYPE_4__ {int /*<<< orphan*/  s_blocksize; } ;
struct TYPE_3__ {scalar_t__ s_maxbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DELAYSTARTBLOCK ; 
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 scalar_t__ HOLESTARTBLOCK ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int XFS_BMAPI_ENTIRE ; 
 scalar_t__ XFS_B_TO_FSB (struct xfs_mount*,scalar_t__) ; 
 scalar_t__ XFS_B_TO_FSBT (struct xfs_mount*,scalar_t__) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 struct xfs_inode* XFS_I (struct inode*) ; 
 int /*<<< orphan*/  XFS_ILOCK_SHARED ; 
 int /*<<< orphan*/  XFS_IOLOCK_EXCL ; 
 scalar_t__ XFS_IS_REALTIME_INODE (struct xfs_inode*) ; 
 int XFS_PREALLOC_SET ; 
 int XFS_PREALLOC_SYNC ; 
 int filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 
 scalar_t__ max (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_bmapi_read (struct xfs_inode*,scalar_t__,scalar_t__,struct xfs_bmbt_irec*,int*,int) ; 
 int xfs_bmbt_to_iomap (struct xfs_inode*,struct iomap*,struct xfs_bmbt_irec*,int) ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ilock_data_map_shared (struct xfs_inode*) ; 
 int xfs_iomap_write_direct (struct xfs_inode*,scalar_t__,scalar_t__,struct xfs_bmbt_irec*,int) ; 
 scalar_t__ xfs_is_reflink_inode (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_update_prealloc_flags (struct xfs_inode*,int) ; 

int
xfs_fs_map_blocks(
	struct inode		*inode,
	loff_t			offset,
	u64			length,
	struct iomap		*iomap,
	bool			write,
	u32			*device_generation)
{
	struct xfs_inode	*ip = XFS_I(inode);
	struct xfs_mount	*mp = ip->i_mount;
	struct xfs_bmbt_irec	imap;
	xfs_fileoff_t		offset_fsb, end_fsb;
	loff_t			limit;
	int			bmapi_flags = XFS_BMAPI_ENTIRE;
	int			nimaps = 1;
	uint			lock_flags;
	int			error = 0;

	if (XFS_FORCED_SHUTDOWN(mp))
		return -EIO;

	/*
	 * We can't export inodes residing on the realtime device.  The realtime
	 * device doesn't have a UUID to identify it, so the client has no way
	 * to find it.
	 */
	if (XFS_IS_REALTIME_INODE(ip))
		return -ENXIO;

	/*
	 * The pNFS block layout spec actually supports reflink like
	 * functionality, but the Linux pNFS server doesn't implement it yet.
	 */
	if (xfs_is_reflink_inode(ip))
		return -ENXIO;

	/*
	 * Lock out any other I/O before we flush and invalidate the pagecache,
	 * and then hand out a layout to the remote system.  This is very
	 * similar to direct I/O, except that the synchronization is much more
	 * complicated.  See the comment near xfs_break_leased_layouts
	 * for a detailed explanation.
	 */
	xfs_ilock(ip, XFS_IOLOCK_EXCL);

	error = -EINVAL;
	limit = mp->m_super->s_maxbytes;
	if (!write)
		limit = max(limit, round_up(i_size_read(inode),
				     inode->i_sb->s_blocksize));
	if (offset > limit)
		goto out_unlock;
	if (offset > limit - length)
		length = limit - offset;

	error = filemap_write_and_wait(inode->i_mapping);
	if (error)
		goto out_unlock;
	error = invalidate_inode_pages2(inode->i_mapping);
	if (WARN_ON_ONCE(error))
		return error;

	end_fsb = XFS_B_TO_FSB(mp, (xfs_ufsize_t)offset + length);
	offset_fsb = XFS_B_TO_FSBT(mp, offset);

	lock_flags = xfs_ilock_data_map_shared(ip);
	error = xfs_bmapi_read(ip, offset_fsb, end_fsb - offset_fsb,
				&imap, &nimaps, bmapi_flags);
	xfs_iunlock(ip, lock_flags);

	if (error)
		goto out_unlock;

	if (write) {
		enum xfs_prealloc_flags	flags = 0;

		ASSERT(imap.br_startblock != DELAYSTARTBLOCK);

		if (!nimaps || imap.br_startblock == HOLESTARTBLOCK) {
			/*
			 * xfs_iomap_write_direct() expects to take ownership of
			 * the shared ilock.
			 */
			xfs_ilock(ip, XFS_ILOCK_SHARED);
			error = xfs_iomap_write_direct(ip, offset, length,
						       &imap, nimaps);
			if (error)
				goto out_unlock;

			/*
			 * Ensure the next transaction is committed
			 * synchronously so that the blocks allocated and
			 * handed out to the client are guaranteed to be
			 * present even after a server crash.
			 */
			flags |= XFS_PREALLOC_SET | XFS_PREALLOC_SYNC;
		}

		error = xfs_update_prealloc_flags(ip, flags);
		if (error)
			goto out_unlock;
	}
	xfs_iunlock(ip, XFS_IOLOCK_EXCL);

	error = xfs_bmbt_to_iomap(ip, iomap, &imap, false);
	*device_generation = mp->m_generation;
	return error;
out_unlock:
	xfs_iunlock(ip, XFS_IOLOCK_EXCL);
	return error;
}