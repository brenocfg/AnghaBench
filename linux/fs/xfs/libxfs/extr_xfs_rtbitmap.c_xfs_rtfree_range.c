#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  scalar_t__ xfs_rtblock_t ;
struct TYPE_9__ {scalar_t__ sb_rextents; } ;
struct TYPE_10__ {TYPE_1__ m_sb; } ;
typedef  TYPE_2__ xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  scalar_t__ xfs_extlen_t ;
typedef  int /*<<< orphan*/  xfs_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BITTOBLOCK (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  XFS_RTBLOCKLOG (scalar_t__) ; 
 int xfs_rtfind_back (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int xfs_rtfind_forw (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__*) ; 
 int xfs_rtmodify_range (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 int xfs_rtmodify_summary (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int
xfs_rtfree_range(
	xfs_mount_t	*mp,		/* file system mount point */
	xfs_trans_t	*tp,		/* transaction pointer */
	xfs_rtblock_t	start,		/* starting block to free */
	xfs_extlen_t	len,		/* length to free */
	xfs_buf_t	**rbpp,		/* in/out: summary block buffer */
	xfs_fsblock_t	*rsb)		/* in/out: summary block number */
{
	xfs_rtblock_t	end;		/* end of the freed extent */
	int		error;		/* error value */
	xfs_rtblock_t	postblock;	/* first block freed > end */
	xfs_rtblock_t	preblock;	/* first block freed < start */

	end = start + len - 1;
	/*
	 * Modify the bitmap to mark this extent freed.
	 */
	error = xfs_rtmodify_range(mp, tp, start, len, 1);
	if (error) {
		return error;
	}
	/*
	 * Assume we're freeing out of the middle of an allocated extent.
	 * We need to find the beginning and end of the extent so we can
	 * properly update the summary.
	 */
	error = xfs_rtfind_back(mp, tp, start, 0, &preblock);
	if (error) {
		return error;
	}
	/*
	 * Find the next allocated block (end of allocated extent).
	 */
	error = xfs_rtfind_forw(mp, tp, end, mp->m_sb.sb_rextents - 1,
		&postblock);
	if (error)
		return error;
	/*
	 * If there are blocks not being freed at the front of the
	 * old extent, add summary data for them to be allocated.
	 */
	if (preblock < start) {
		error = xfs_rtmodify_summary(mp, tp,
			XFS_RTBLOCKLOG(start - preblock),
			XFS_BITTOBLOCK(mp, preblock), -1, rbpp, rsb);
		if (error) {
			return error;
		}
	}
	/*
	 * If there are blocks not being freed at the end of the
	 * old extent, add summary data for them to be allocated.
	 */
	if (postblock > end) {
		error = xfs_rtmodify_summary(mp, tp,
			XFS_RTBLOCKLOG(postblock - end),
			XFS_BITTOBLOCK(mp, end + 1), -1, rbpp, rsb);
		if (error) {
			return error;
		}
	}
	/*
	 * Increment the summary information corresponding to the entire
	 * (new) free extent.
	 */
	error = xfs_rtmodify_summary(mp, tp,
		XFS_RTBLOCKLOG(postblock + 1 - preblock),
		XFS_BITTOBLOCK(mp, preblock), 1, rbpp, rsb);
	return error;
}