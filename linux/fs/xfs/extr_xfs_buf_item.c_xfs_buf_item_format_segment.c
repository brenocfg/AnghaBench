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
typedef  int uint ;
struct xfs_log_vec {int dummy; } ;
struct xfs_log_iovec {int dummy; } ;
struct TYPE_2__ {int blf_flags; } ;
struct xfs_buf_log_item {int bli_flags; TYPE_1__ __bli_format; struct xfs_buf* bli_buf; } ;
struct xfs_buf_log_format {int blf_flags; int blf_size; int /*<<< orphan*/  blf_map_size; int /*<<< orphan*/  blf_data_map; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_BLF_CANCEL ; 
 int XFS_BLI_STALE ; 
 int /*<<< orphan*/  XLOG_REG_TYPE_BFORMAT ; 
 int /*<<< orphan*/  trace_xfs_buf_item_format_stale (struct xfs_buf_log_item*) ; 
 int /*<<< orphan*/  xfs_buf_item_copy_iovec (struct xfs_log_vec*,struct xfs_log_iovec**,struct xfs_buf*,int,int,int) ; 
 scalar_t__ xfs_buf_item_straddle (struct xfs_buf*,int,int,int) ; 
 int xfs_buf_log_format_size (struct xfs_buf_log_format*) ; 
 int xfs_next_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct xfs_buf_log_format* xlog_copy_iovec (struct xfs_log_vec*,struct xfs_log_iovec**,int /*<<< orphan*/ ,struct xfs_buf_log_format*,int) ; 

__attribute__((used)) static void
xfs_buf_item_format_segment(
	struct xfs_buf_log_item	*bip,
	struct xfs_log_vec	*lv,
	struct xfs_log_iovec	**vecp,
	uint			offset,
	struct xfs_buf_log_format *blfp)
{
	struct xfs_buf		*bp = bip->bli_buf;
	uint			base_size;
	int			first_bit;
	int			last_bit;
	int			next_bit;
	uint			nbits;

	/* copy the flags across from the base format item */
	blfp->blf_flags = bip->__bli_format.blf_flags;

	/*
	 * Base size is the actual size of the ondisk structure - it reflects
	 * the actual size of the dirty bitmap rather than the size of the in
	 * memory structure.
	 */
	base_size = xfs_buf_log_format_size(blfp);

	first_bit = xfs_next_bit(blfp->blf_data_map, blfp->blf_map_size, 0);
	if (!(bip->bli_flags & XFS_BLI_STALE) && first_bit == -1) {
		/*
		 * If the map is not be dirty in the transaction, mark
		 * the size as zero and do not advance the vector pointer.
		 */
		return;
	}

	blfp = xlog_copy_iovec(lv, vecp, XLOG_REG_TYPE_BFORMAT, blfp, base_size);
	blfp->blf_size = 1;

	if (bip->bli_flags & XFS_BLI_STALE) {
		/*
		 * The buffer is stale, so all we need to log
		 * is the buf log format structure with the
		 * cancel flag in it.
		 */
		trace_xfs_buf_item_format_stale(bip);
		ASSERT(blfp->blf_flags & XFS_BLF_CANCEL);
		return;
	}


	/*
	 * Fill in an iovec for each set of contiguous chunks.
	 */
	last_bit = first_bit;
	nbits = 1;
	for (;;) {
		/*
		 * This takes the bit number to start looking from and
		 * returns the next set bit from there.  It returns -1
		 * if there are no more bits set or the start bit is
		 * beyond the end of the bitmap.
		 */
		next_bit = xfs_next_bit(blfp->blf_data_map, blfp->blf_map_size,
					(uint)last_bit + 1);
		/*
		 * If we run out of bits fill in the last iovec and get out of
		 * the loop.  Else if we start a new set of bits then fill in
		 * the iovec for the series we were looking at and start
		 * counting the bits in the new one.  Else we're still in the
		 * same set of bits so just keep counting and scanning.
		 */
		if (next_bit == -1) {
			xfs_buf_item_copy_iovec(lv, vecp, bp, offset,
						first_bit, nbits);
			blfp->blf_size++;
			break;
		} else if (next_bit != last_bit + 1 ||
		           xfs_buf_item_straddle(bp, offset, next_bit, last_bit)) {
			xfs_buf_item_copy_iovec(lv, vecp, bp, offset,
						first_bit, nbits);
			blfp->blf_size++;
			first_bit = next_bit;
			last_bit = next_bit;
			nbits = 1;
		} else {
			last_bit++;
			nbits++;
		}
	}
}