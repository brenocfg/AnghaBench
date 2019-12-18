#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  int xfs_suminfo_t ;
typedef  size_t xfs_rtblock_t ;
struct TYPE_13__ {int* m_rsum_cache; } ;
typedef  TYPE_1__ xfs_mount_t ;
typedef  scalar_t__ xfs_fsblock_t ;
struct TYPE_14__ {scalar_t__ b_addr; } ;
typedef  TYPE_2__ xfs_buf_t ;
typedef  scalar_t__ uint ;

/* Variables and functions */
 int XFS_SUMOFFS (TYPE_1__*,int,size_t) ; 
 scalar_t__ XFS_SUMOFFSTOBLOCK (TYPE_1__*,int) ; 
 int* XFS_SUMPTR (TYPE_1__*,TYPE_2__*,int) ; 
 int xfs_rtbuf_get (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int,TYPE_2__**) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,scalar_t__) ; 

int
xfs_rtmodify_summary_int(
	xfs_mount_t	*mp,		/* file system mount structure */
	xfs_trans_t	*tp,		/* transaction pointer */
	int		log,		/* log2 of extent size */
	xfs_rtblock_t	bbno,		/* bitmap block number */
	int		delta,		/* change to make to summary info */
	xfs_buf_t	**rbpp,		/* in/out: summary block buffer */
	xfs_fsblock_t	*rsb,		/* in/out: summary block number */
	xfs_suminfo_t	*sum)		/* out: summary info for this block */
{
	xfs_buf_t	*bp;		/* buffer for the summary block */
	int		error;		/* error value */
	xfs_fsblock_t	sb;		/* summary fsblock */
	int		so;		/* index into the summary file */
	xfs_suminfo_t	*sp;		/* pointer to returned data */

	/*
	 * Compute entry number in the summary file.
	 */
	so = XFS_SUMOFFS(mp, log, bbno);
	/*
	 * Compute the block number in the summary file.
	 */
	sb = XFS_SUMOFFSTOBLOCK(mp, so);
	/*
	 * If we have an old buffer, and the block number matches, use that.
	 */
	if (*rbpp && *rsb == sb)
		bp = *rbpp;
	/*
	 * Otherwise we have to get the buffer.
	 */
	else {
		/*
		 * If there was an old one, get rid of it first.
		 */
		if (*rbpp)
			xfs_trans_brelse(tp, *rbpp);
		error = xfs_rtbuf_get(mp, tp, sb, 1, &bp);
		if (error) {
			return error;
		}
		/*
		 * Remember this buffer and block for the next call.
		 */
		*rbpp = bp;
		*rsb = sb;
	}
	/*
	 * Point to the summary information, modify/log it, and/or copy it out.
	 */
	sp = XFS_SUMPTR(mp, bp, so);
	if (delta) {
		uint first = (uint)((char *)sp - (char *)bp->b_addr);

		*sp += delta;
		if (mp->m_rsum_cache) {
			if (*sp == 0 && log == mp->m_rsum_cache[bbno])
				mp->m_rsum_cache[bbno]++;
			if (*sp != 0 && log < mp->m_rsum_cache[bbno])
				mp->m_rsum_cache[bbno] = log;
		}
		xfs_trans_log_buf(tp, bp, first, first + sizeof(*sp) - 1);
	}
	if (sum)
		*sum = *sp;
	return 0;
}