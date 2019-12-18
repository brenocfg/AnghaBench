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
typedef  scalar_t__ xfs_off_t ;
typedef  scalar_t__ xfs_fileoff_t ;
struct xfs_inode {int /*<<< orphan*/  i_mount; } ;

/* Variables and functions */
 scalar_t__ XFS_B_TO_FSB (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ XFS_B_TO_FSBT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  trace_xfs_reflink_end_cow (struct xfs_inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_reflink_end_cow_error (struct xfs_inode*,int,int /*<<< orphan*/ ) ; 
 int xfs_reflink_end_cow_extent (struct xfs_inode*,scalar_t__,scalar_t__*) ; 

int
xfs_reflink_end_cow(
	struct xfs_inode		*ip,
	xfs_off_t			offset,
	xfs_off_t			count)
{
	xfs_fileoff_t			offset_fsb;
	xfs_fileoff_t			end_fsb;
	int				error = 0;

	trace_xfs_reflink_end_cow(ip, offset, count);

	offset_fsb = XFS_B_TO_FSBT(ip->i_mount, offset);
	end_fsb = XFS_B_TO_FSB(ip->i_mount, offset + count);

	/*
	 * Walk backwards until we're out of the I/O range.  The loop function
	 * repeatedly cycles the ILOCK to allocate one transaction per remapped
	 * extent.
	 *
	 * If we're being called by writeback then the the pages will still
	 * have PageWriteback set, which prevents races with reflink remapping
	 * and truncate.  Reflink remapping prevents races with writeback by
	 * taking the iolock and mmaplock before flushing the pages and
	 * remapping, which means there won't be any further writeback or page
	 * cache dirtying until the reflink completes.
	 *
	 * We should never have two threads issuing writeback for the same file
	 * region.  There are also have post-eof checks in the writeback
	 * preparation code so that we don't bother writing out pages that are
	 * about to be truncated.
	 *
	 * If we're being called as part of directio write completion, the dio
	 * count is still elevated, which reflink and truncate will wait for.
	 * Reflink remapping takes the iolock and mmaplock and waits for
	 * pending dio to finish, which should prevent any directio until the
	 * remap completes.  Multiple concurrent directio writes to the same
	 * region are handled by end_cow processing only occurring for the
	 * threads which succeed; the outcome of multiple overlapping direct
	 * writes is not well defined anyway.
	 *
	 * It's possible that a buffered write and a direct write could collide
	 * here (the buffered write stumbles in after the dio flushes and
	 * invalidates the page cache and immediately queues writeback), but we
	 * have never supported this 100%.  If either disk write succeeds the
	 * blocks will be remapped.
	 */
	while (end_fsb > offset_fsb && !error)
		error = xfs_reflink_end_cow_extent(ip, offset_fsb, &end_fsb);

	if (error)
		trace_xfs_reflink_end_cow_error(ip, error, _RET_IP_);
	return error;
}