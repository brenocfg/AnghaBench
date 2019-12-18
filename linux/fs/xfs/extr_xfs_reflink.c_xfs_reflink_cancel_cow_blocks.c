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
typedef  scalar_t__ xfs_fileoff_t ;
struct xfs_trans {scalar_t__ t_firstblock; } ;
struct xfs_inode {int dummy; } ;
struct xfs_ifork {int /*<<< orphan*/  if_bytes; } ;
struct xfs_iext_cursor {int dummy; } ;
struct xfs_bmbt_irec {scalar_t__ br_startoff; scalar_t__ br_blockcount; scalar_t__ br_state; int /*<<< orphan*/  br_startblock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ NULLFSBLOCK ; 
 int /*<<< orphan*/  XFS_COW_FORK ; 
 scalar_t__ XFS_EXT_UNWRITTEN ; 
 struct xfs_ifork* XFS_IFORK_PTR (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_QMOPT_RES_REGBLKS ; 
 scalar_t__ isnullstartblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_reflink_cancel_cow (struct xfs_inode*,struct xfs_bmbt_irec*) ; 
 int /*<<< orphan*/  xfs_bmap_add_free (struct xfs_trans*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_bmap_del_extent_cow (struct xfs_inode*,struct xfs_iext_cursor*,struct xfs_bmbt_irec*,struct xfs_bmbt_irec*) ; 
 int xfs_bmap_del_extent_delay (struct xfs_inode*,int /*<<< orphan*/ ,struct xfs_iext_cursor*,struct xfs_bmbt_irec*,struct xfs_bmbt_irec*) ; 
 int xfs_defer_finish (struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_iext_get_extent (struct xfs_ifork*,struct xfs_iext_cursor*,struct xfs_bmbt_irec*) ; 
 int /*<<< orphan*/  xfs_iext_lookup_extent_before (struct xfs_inode*,struct xfs_ifork*,scalar_t__*,struct xfs_iext_cursor*,struct xfs_bmbt_irec*) ; 
 int /*<<< orphan*/  xfs_iext_prev (struct xfs_ifork*,struct xfs_iext_cursor*) ; 
 int /*<<< orphan*/  xfs_inode_clear_cowblocks_tag (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_inode_has_cow_data (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_refcount_free_cow_extent (struct xfs_trans*,int /*<<< orphan*/ ,scalar_t__) ; 
 int xfs_trans_reserve_quota_nblks (int /*<<< orphan*/ *,struct xfs_inode*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trim_extent (struct xfs_bmbt_irec*,scalar_t__,scalar_t__) ; 

int
xfs_reflink_cancel_cow_blocks(
	struct xfs_inode		*ip,
	struct xfs_trans		**tpp,
	xfs_fileoff_t			offset_fsb,
	xfs_fileoff_t			end_fsb,
	bool				cancel_real)
{
	struct xfs_ifork		*ifp = XFS_IFORK_PTR(ip, XFS_COW_FORK);
	struct xfs_bmbt_irec		got, del;
	struct xfs_iext_cursor		icur;
	int				error = 0;

	if (!xfs_inode_has_cow_data(ip))
		return 0;
	if (!xfs_iext_lookup_extent_before(ip, ifp, &end_fsb, &icur, &got))
		return 0;

	/* Walk backwards until we're out of the I/O range... */
	while (got.br_startoff + got.br_blockcount > offset_fsb) {
		del = got;
		xfs_trim_extent(&del, offset_fsb, end_fsb - offset_fsb);

		/* Extent delete may have bumped ext forward */
		if (!del.br_blockcount) {
			xfs_iext_prev(ifp, &icur);
			goto next_extent;
		}

		trace_xfs_reflink_cancel_cow(ip, &del);

		if (isnullstartblock(del.br_startblock)) {
			error = xfs_bmap_del_extent_delay(ip, XFS_COW_FORK,
					&icur, &got, &del);
			if (error)
				break;
		} else if (del.br_state == XFS_EXT_UNWRITTEN || cancel_real) {
			ASSERT((*tpp)->t_firstblock == NULLFSBLOCK);

			/* Free the CoW orphan record. */
			xfs_refcount_free_cow_extent(*tpp, del.br_startblock,
					del.br_blockcount);

			xfs_bmap_add_free(*tpp, del.br_startblock,
					  del.br_blockcount, NULL);

			/* Roll the transaction */
			error = xfs_defer_finish(tpp);
			if (error)
				break;

			/* Remove the mapping from the CoW fork. */
			xfs_bmap_del_extent_cow(ip, &icur, &got, &del);

			/* Remove the quota reservation */
			error = xfs_trans_reserve_quota_nblks(NULL, ip,
					-(long)del.br_blockcount, 0,
					XFS_QMOPT_RES_REGBLKS);
			if (error)
				break;
		} else {
			/* Didn't do anything, push cursor back. */
			xfs_iext_prev(ifp, &icur);
		}
next_extent:
		if (!xfs_iext_get_extent(ifp, &icur, &got))
			break;
	}

	/* clear tag if cow fork is emptied */
	if (!ifp->if_bytes)
		xfs_inode_clear_cowblocks_tag(ip);
	return error;
}