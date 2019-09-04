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
struct xfs_buf {int b_flags; int /*<<< orphan*/  b_io_remaining; int /*<<< orphan*/  b_addr; int /*<<< orphan*/  b_error; int /*<<< orphan*/  b_io_error; } ;
struct bio {scalar_t__ bi_status; scalar_t__ bi_private; } ;

/* Variables and functions */
 int XBF_READ ; 
 int atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int blk_status_to_errno (scalar_t__) ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  invalidate_kernel_vmap_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_ioend_async (struct xfs_buf*) ; 
 scalar_t__ xfs_buf_is_vmapped (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_vmap_len (struct xfs_buf*) ; 

__attribute__((used)) static void
xfs_buf_bio_end_io(
	struct bio		*bio)
{
	struct xfs_buf		*bp = (struct xfs_buf *)bio->bi_private;

	/*
	 * don't overwrite existing errors - otherwise we can lose errors on
	 * buffers that require multiple bios to complete.
	 */
	if (bio->bi_status) {
		int error = blk_status_to_errno(bio->bi_status);

		cmpxchg(&bp->b_io_error, 0, error);
	}

	if (!bp->b_error && xfs_buf_is_vmapped(bp) && (bp->b_flags & XBF_READ))
		invalidate_kernel_vmap_range(bp->b_addr, xfs_buf_vmap_len(bp));

	if (atomic_dec_and_test(&bp->b_io_remaining) == 1)
		xfs_buf_ioend_async(bp);
	bio_put(bio);
}