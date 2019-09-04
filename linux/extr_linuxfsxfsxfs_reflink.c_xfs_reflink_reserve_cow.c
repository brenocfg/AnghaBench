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
struct xfs_inode {int dummy; } ;
struct xfs_ifork {int dummy; } ;
struct xfs_iext_cursor {int dummy; } ;
struct xfs_bmbt_irec {scalar_t__ br_startoff; int /*<<< orphan*/  br_blockcount; } ;

/* Variables and functions */
 int EDQUOT ; 
 int ENOSPC ; 
 int /*<<< orphan*/  XFS_COW_FORK ; 
 struct xfs_ifork* XFS_IFORK_PTR (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_reflink_cow_alloc (struct xfs_inode*,struct xfs_bmbt_irec*) ; 
 int /*<<< orphan*/  trace_xfs_reflink_cow_enospc (struct xfs_inode*,struct xfs_bmbt_irec*) ; 
 int /*<<< orphan*/  trace_xfs_reflink_cow_found (struct xfs_inode*,struct xfs_bmbt_irec*) ; 
 int xfs_bmapi_reserve_delalloc (struct xfs_inode*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_bmbt_irec*,struct xfs_iext_cursor*,int) ; 
 int /*<<< orphan*/  xfs_iext_lookup_extent (struct xfs_inode*,struct xfs_ifork*,scalar_t__,struct xfs_iext_cursor*,struct xfs_bmbt_irec*) ; 
 int xfs_qm_dqattach_locked (struct xfs_inode*,int) ; 
 int xfs_reflink_trim_around_shared (struct xfs_inode*,struct xfs_bmbt_irec*,int*,int*) ; 
 int /*<<< orphan*/  xfs_trim_extent (struct xfs_bmbt_irec*,scalar_t__,int /*<<< orphan*/ ) ; 

int
xfs_reflink_reserve_cow(
	struct xfs_inode	*ip,
	struct xfs_bmbt_irec	*imap,
	bool			*shared)
{
	struct xfs_ifork	*ifp = XFS_IFORK_PTR(ip, XFS_COW_FORK);
	struct xfs_bmbt_irec	got;
	int			error = 0;
	bool			eof = false, trimmed;
	struct xfs_iext_cursor	icur;

	/*
	 * Search the COW fork extent list first.  This serves two purposes:
	 * first this implement the speculative preallocation using cowextisze,
	 * so that we also unshared block adjacent to shared blocks instead
	 * of just the shared blocks themselves.  Second the lookup in the
	 * extent list is generally faster than going out to the shared extent
	 * tree.
	 */

	if (!xfs_iext_lookup_extent(ip, ifp, imap->br_startoff, &icur, &got))
		eof = true;
	if (!eof && got.br_startoff <= imap->br_startoff) {
		trace_xfs_reflink_cow_found(ip, imap);
		xfs_trim_extent(imap, got.br_startoff, got.br_blockcount);

		*shared = true;
		return 0;
	}

	/* Trim the mapping to the nearest shared extent boundary. */
	error = xfs_reflink_trim_around_shared(ip, imap, shared, &trimmed);
	if (error)
		return error;

	/* Not shared?  Just report the (potentially capped) extent. */
	if (!*shared)
		return 0;

	/*
	 * Fork all the shared blocks from our write offset until the end of
	 * the extent.
	 */
	error = xfs_qm_dqattach_locked(ip, false);
	if (error)
		return error;

	error = xfs_bmapi_reserve_delalloc(ip, XFS_COW_FORK, imap->br_startoff,
			imap->br_blockcount, 0, &got, &icur, eof);
	if (error == -ENOSPC || error == -EDQUOT)
		trace_xfs_reflink_cow_enospc(ip, imap);
	if (error)
		return error;

	xfs_trim_extent(imap, got.br_startoff, got.br_blockcount);
	trace_xfs_reflink_cow_alloc(ip, &got);
	return 0;
}