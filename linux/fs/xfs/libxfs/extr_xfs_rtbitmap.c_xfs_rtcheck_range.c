#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  int xfs_rtword_t ;
typedef  int xfs_rtblock_t ;
typedef  int /*<<< orphan*/  xfs_mount_t ;
typedef  int xfs_extlen_t ;
struct TYPE_4__ {int* b_addr; } ;
typedef  TYPE_1__ xfs_buf_t ;

/* Variables and functions */
 int XFS_BITTOBLOCK (int /*<<< orphan*/ *,int) ; 
 int XFS_BITTOWORD (int /*<<< orphan*/ *,int) ; 
 int XFS_BLOCKWSIZE (int /*<<< orphan*/ *) ; 
 int XFS_NBWORD ; 
 int XFS_RTLOBIT (int) ; 
 int XFS_RTMIN (int,int) ; 
 int xfs_rtbuf_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
xfs_rtcheck_range(
	xfs_mount_t	*mp,		/* file system mount point */
	xfs_trans_t	*tp,		/* transaction pointer */
	xfs_rtblock_t	start,		/* starting block number of extent */
	xfs_extlen_t	len,		/* length of extent */
	int		val,		/* 1 for free, 0 for allocated */
	xfs_rtblock_t	*new,		/* out: first block not matching */
	int		*stat)		/* out: 1 for matches, 0 for not */
{
	xfs_rtword_t	*b;		/* current word in buffer */
	int		bit;		/* bit number in the word */
	xfs_rtblock_t	block;		/* bitmap block number */
	xfs_buf_t	*bp;		/* buf for the block */
	xfs_rtword_t	*bufp;		/* starting word in buffer */
	int		error;		/* error value */
	xfs_rtblock_t	i;		/* current bit number rel. to start */
	xfs_rtblock_t	lastbit;	/* last useful bit in word */
	xfs_rtword_t	mask;		/* mask of relevant bits for value */
	xfs_rtword_t	wdiff;		/* difference from wanted value */
	int		word;		/* word number in the buffer */

	/*
	 * Compute starting bitmap block number
	 */
	block = XFS_BITTOBLOCK(mp, start);
	/*
	 * Read the bitmap block.
	 */
	error = xfs_rtbuf_get(mp, tp, block, 0, &bp);
	if (error) {
		return error;
	}
	bufp = bp->b_addr;
	/*
	 * Compute the starting word's address, and starting bit.
	 */
	word = XFS_BITTOWORD(mp, start);
	b = &bufp[word];
	bit = (int)(start & (XFS_NBWORD - 1));
	/*
	 * 0 (allocated) => all zero's; 1 (free) => all one's.
	 */
	val = -val;
	/*
	 * If not starting on a word boundary, deal with the first
	 * (partial) word.
	 */
	if (bit) {
		/*
		 * Compute first bit not examined.
		 */
		lastbit = XFS_RTMIN(bit + len, XFS_NBWORD);
		/*
		 * Mask of relevant bits.
		 */
		mask = (((xfs_rtword_t)1 << (lastbit - bit)) - 1) << bit;
		/*
		 * Compute difference between actual and desired value.
		 */
		if ((wdiff = (*b ^ val) & mask)) {
			/*
			 * Different, compute first wrong bit and return.
			 */
			xfs_trans_brelse(tp, bp);
			i = XFS_RTLOBIT(wdiff) - bit;
			*new = start + i;
			*stat = 0;
			return 0;
		}
		i = lastbit - bit;
		/*
		 * Go on to next block if that's where the next word is
		 * and we need the next word.
		 */
		if (++word == XFS_BLOCKWSIZE(mp) && i < len) {
			/*
			 * If done with this block, get the next one.
			 */
			xfs_trans_brelse(tp, bp);
			error = xfs_rtbuf_get(mp, tp, ++block, 0, &bp);
			if (error) {
				return error;
			}
			b = bufp = bp->b_addr;
			word = 0;
		} else {
			/*
			 * Go on to the next word in the buffer.
			 */
			b++;
		}
	} else {
		/*
		 * Starting on a word boundary, no partial word.
		 */
		i = 0;
	}
	/*
	 * Loop over whole words in buffers.  When we use up one buffer
	 * we move on to the next one.
	 */
	while (len - i >= XFS_NBWORD) {
		/*
		 * Compute difference between actual and desired value.
		 */
		if ((wdiff = *b ^ val)) {
			/*
			 * Different, compute first wrong bit and return.
			 */
			xfs_trans_brelse(tp, bp);
			i += XFS_RTLOBIT(wdiff);
			*new = start + i;
			*stat = 0;
			return 0;
		}
		i += XFS_NBWORD;
		/*
		 * Go on to next block if that's where the next word is
		 * and we need the next word.
		 */
		if (++word == XFS_BLOCKWSIZE(mp) && i < len) {
			/*
			 * If done with this block, get the next one.
			 */
			xfs_trans_brelse(tp, bp);
			error = xfs_rtbuf_get(mp, tp, ++block, 0, &bp);
			if (error) {
				return error;
			}
			b = bufp = bp->b_addr;
			word = 0;
		} else {
			/*
			 * Go on to the next word in the buffer.
			 */
			b++;
		}
	}
	/*
	 * If not ending on a word boundary, deal with the last
	 * (partial) word.
	 */
	if ((lastbit = len - i)) {
		/*
		 * Mask of relevant bits.
		 */
		mask = ((xfs_rtword_t)1 << lastbit) - 1;
		/*
		 * Compute difference between actual and desired value.
		 */
		if ((wdiff = (*b ^ val) & mask)) {
			/*
			 * Different, compute first wrong bit and return.
			 */
			xfs_trans_brelse(tp, bp);
			i += XFS_RTLOBIT(wdiff);
			*new = start + i;
			*stat = 0;
			return 0;
		} else
			i = len;
	}
	/*
	 * Successful, return.
	 */
	xfs_trans_brelse(tp, bp);
	*new = start + i;
	*stat = 1;
	return 0;
}