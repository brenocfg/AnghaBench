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
typedef  scalar_t__ xfs_off_t ;
typedef  scalar_t__ xfs_fileoff_t ;
typedef  scalar_t__ xfs_filblks_t ;
struct xfs_trans {scalar_t__ t_firstblock; } ;
struct xfs_inode {int /*<<< orphan*/  i_mount; } ;
struct xfs_ifork {scalar_t__ if_bytes; } ;
struct xfs_iext_cursor {int dummy; } ;
struct xfs_bmbt_irec {scalar_t__ br_startoff; scalar_t__ br_blockcount; int /*<<< orphan*/  br_startblock; } ;
struct TYPE_2__ {int /*<<< orphan*/  tr_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EFSCORRUPTED ; 
 scalar_t__ MAX_RW_COUNT ; 
 TYPE_1__* M_RES (int /*<<< orphan*/ ) ; 
 scalar_t__ NULLFSBLOCK ; 
 int /*<<< orphan*/  SHUTDOWN_CORRUPT_INCORE ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ XFS_B_TO_FSB (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ XFS_B_TO_FSBT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XFS_COW_FORK ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 struct xfs_ifork* XFS_IFORK_PTR (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 unsigned int XFS_NEXTENTADD_SPACE_RES (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_TRANS_DQ_DELBCOUNT ; 
 int XFS_TRANS_NOFS ; 
 int XFS_TRANS_RESERVE ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int __xfs_bunmapi (struct xfs_trans*,struct xfs_inode*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_xfs_reflink_cow_remap (struct xfs_inode*,struct xfs_bmbt_irec*) ; 
 int /*<<< orphan*/  trace_xfs_reflink_end_cow (struct xfs_inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_reflink_end_cow_error (struct xfs_inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_bmap_del_extent_cow (struct xfs_inode*,struct xfs_iext_cursor*,struct xfs_bmbt_irec*,struct xfs_bmbt_irec*) ; 
 int /*<<< orphan*/  xfs_bmap_is_real_extent (struct xfs_bmbt_irec*) ; 
 int xfs_bmap_map_extent (struct xfs_trans*,struct xfs_inode*,struct xfs_bmbt_irec*) ; 
 int xfs_defer_finish (struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_force_shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iext_get_extent (struct xfs_ifork*,struct xfs_iext_cursor*,struct xfs_bmbt_irec*) ; 
 int /*<<< orphan*/  xfs_iext_lookup_extent_before (struct xfs_inode*,struct xfs_ifork*,scalar_t__*,struct xfs_iext_cursor*,struct xfs_bmbt_irec*) ; 
 int /*<<< orphan*/  xfs_iext_prev_extent (struct xfs_ifork*,struct xfs_iext_cursor*,struct xfs_bmbt_irec*) ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_refcount_free_cow_extent (struct xfs_trans*,int /*<<< orphan*/ ,scalar_t__) ; 
 int xfs_trans_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int,struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_trans_cancel (struct xfs_trans*) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_mod_dquot_byino (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  xfs_trim_extent (struct xfs_bmbt_irec*,scalar_t__,scalar_t__) ; 

int
xfs_reflink_end_cow(
	struct xfs_inode		*ip,
	xfs_off_t			offset,
	xfs_off_t			count)
{
	struct xfs_ifork		*ifp = XFS_IFORK_PTR(ip, XFS_COW_FORK);
	struct xfs_bmbt_irec		got, del;
	struct xfs_trans		*tp;
	xfs_fileoff_t			offset_fsb;
	xfs_fileoff_t			end_fsb;
	int				error;
	unsigned int			resblks;
	xfs_filblks_t			rlen;
	struct xfs_iext_cursor		icur;

	trace_xfs_reflink_end_cow(ip, offset, count);

	/* No COW extents?  That's easy! */
	if (ifp->if_bytes == 0)
		return 0;

	offset_fsb = XFS_B_TO_FSBT(ip->i_mount, offset);
	end_fsb = XFS_B_TO_FSB(ip->i_mount, offset + count);

	/*
	 * Start a rolling transaction to switch the mappings.  We're
	 * unlikely ever to have to remap 16T worth of single-block
	 * extents, so just cap the worst case extent count to 2^32-1.
	 * Stick a warning in just in case, and avoid 64-bit division.
	 */
	BUILD_BUG_ON(MAX_RW_COUNT > UINT_MAX);
	if (end_fsb - offset_fsb > UINT_MAX) {
		error = -EFSCORRUPTED;
		xfs_force_shutdown(ip->i_mount, SHUTDOWN_CORRUPT_INCORE);
		ASSERT(0);
		goto out;
	}
	resblks = XFS_NEXTENTADD_SPACE_RES(ip->i_mount,
			(unsigned int)(end_fsb - offset_fsb),
			XFS_DATA_FORK);
	error = xfs_trans_alloc(ip->i_mount, &M_RES(ip->i_mount)->tr_write,
			resblks, 0, XFS_TRANS_RESERVE | XFS_TRANS_NOFS, &tp);
	if (error)
		goto out;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, 0);

	/*
	 * In case of racing, overlapping AIO writes no COW extents might be
	 * left by the time I/O completes for the loser of the race.  In that
	 * case we are done.
	 */
	if (!xfs_iext_lookup_extent_before(ip, ifp, &end_fsb, &icur, &got))
		goto out_cancel;

	/* Walk backwards until we're out of the I/O range... */
	while (got.br_startoff + got.br_blockcount > offset_fsb) {
		del = got;
		xfs_trim_extent(&del, offset_fsb, end_fsb - offset_fsb);

		/* Extent delete may have bumped ext forward */
		if (!del.br_blockcount)
			goto prev_extent;

		/*
		 * Only remap real extent that contain data.  With AIO
		 * speculatively preallocations can leak into the range we
		 * are called upon, and we need to skip them.
		 */
		if (!xfs_bmap_is_real_extent(&got))
			goto prev_extent;

		/* Unmap the old blocks in the data fork. */
		ASSERT(tp->t_firstblock == NULLFSBLOCK);
		rlen = del.br_blockcount;
		error = __xfs_bunmapi(tp, ip, del.br_startoff, &rlen, 0, 1);
		if (error)
			goto out_cancel;

		/* Trim the extent to whatever got unmapped. */
		if (rlen) {
			xfs_trim_extent(&del, del.br_startoff + rlen,
				del.br_blockcount - rlen);
		}
		trace_xfs_reflink_cow_remap(ip, &del);

		/* Free the CoW orphan record. */
		error = xfs_refcount_free_cow_extent(tp, del.br_startblock,
				del.br_blockcount);
		if (error)
			goto out_cancel;

		/* Map the new blocks into the data fork. */
		error = xfs_bmap_map_extent(tp, ip, &del);
		if (error)
			goto out_cancel;

		/* Charge this new data fork mapping to the on-disk quota. */
		xfs_trans_mod_dquot_byino(tp, ip, XFS_TRANS_DQ_DELBCOUNT,
				(long)del.br_blockcount);

		/* Remove the mapping from the CoW fork. */
		xfs_bmap_del_extent_cow(ip, &icur, &got, &del);

		error = xfs_defer_finish(&tp);
		if (error)
			goto out_cancel;
		if (!xfs_iext_get_extent(ifp, &icur, &got))
			break;
		continue;
prev_extent:
		if (!xfs_iext_prev_extent(ifp, &icur, &got))
			break;
	}

	error = xfs_trans_commit(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	if (error)
		goto out;
	return 0;

out_cancel:
	xfs_trans_cancel(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
out:
	trace_xfs_reflink_end_cow_error(ip, error, _RET_IP_);
	return error;
}