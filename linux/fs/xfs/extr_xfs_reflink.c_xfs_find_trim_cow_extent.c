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
typedef  scalar_t__ xfs_filblks_t ;
struct xfs_inode {int /*<<< orphan*/  i_cowfp; } ;
struct xfs_iext_cursor {int dummy; } ;
struct xfs_bmbt_irec {scalar_t__ br_startoff; scalar_t__ br_blockcount; int /*<<< orphan*/  br_startblock; } ;

/* Variables and functions */
 scalar_t__ isnullstartblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iext_lookup_extent (struct xfs_inode*,int /*<<< orphan*/ ,scalar_t__,struct xfs_iext_cursor*,struct xfs_bmbt_irec*) ; 
 int xfs_inode_need_cow (struct xfs_inode*,struct xfs_bmbt_irec*,int*) ; 
 int /*<<< orphan*/  xfs_trim_extent (struct xfs_bmbt_irec*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
xfs_find_trim_cow_extent(
	struct xfs_inode	*ip,
	struct xfs_bmbt_irec	*imap,
	bool			*shared,
	bool			*found)
{
	xfs_fileoff_t		offset_fsb = imap->br_startoff;
	xfs_filblks_t		count_fsb = imap->br_blockcount;
	struct xfs_iext_cursor	icur;
	struct xfs_bmbt_irec	got;

	*found = false;

	/*
	 * If we don't find an overlapping extent, trim the range we need to
	 * allocate to fit the hole we found.
	 */
	if (!xfs_iext_lookup_extent(ip, ip->i_cowfp, offset_fsb, &icur, &got))
		got.br_startoff = offset_fsb + count_fsb;
	if (got.br_startoff > offset_fsb) {
		xfs_trim_extent(imap, imap->br_startoff,
				got.br_startoff - imap->br_startoff);
		return xfs_inode_need_cow(ip, imap, shared);
	}

	*shared = true;
	if (isnullstartblock(got.br_startblock)) {
		xfs_trim_extent(imap, got.br_startoff, got.br_blockcount);
		return 0;
	}

	/* real extent found - no need to allocate */
	xfs_trim_extent(&got, offset_fsb, count_fsb);
	*imap = got;
	*found = true;
	return 0;
}