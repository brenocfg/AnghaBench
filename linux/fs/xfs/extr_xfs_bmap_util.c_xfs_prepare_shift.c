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
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  NULLFILEOFF ; 
 int /*<<< orphan*/  XFS_ISIZE (struct xfs_inode*) ; 
 scalar_t__ xfs_can_free_eofblocks (struct xfs_inode*,int) ; 
 int xfs_flush_unmap_range (struct xfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_free_eofblocks (struct xfs_inode*) ; 
 scalar_t__ xfs_inode_has_cow_data (struct xfs_inode*) ; 
 int xfs_reflink_cancel_cow_range (struct xfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
xfs_prepare_shift(
	struct xfs_inode	*ip,
	loff_t			offset)
{
	int			error;

	/*
	 * Trim eofblocks to avoid shifting uninitialized post-eof preallocation
	 * into the accessible region of the file.
	 */
	if (xfs_can_free_eofblocks(ip, true)) {
		error = xfs_free_eofblocks(ip);
		if (error)
			return error;
	}

	/*
	 * Writeback and invalidate cache for the remainder of the file as we're
	 * about to shift down every extent from offset to EOF.
	 */
	error = xfs_flush_unmap_range(ip, offset, XFS_ISIZE(ip));
	if (error)
		return error;

	/*
	 * Clean out anything hanging around in the cow fork now that
	 * we've flushed all the dirty data out to disk to avoid having
	 * CoW extents at the wrong offsets.
	 */
	if (xfs_inode_has_cow_data(ip)) {
		error = xfs_reflink_cancel_cow_range(ip, offset, NULLFILEOFF,
				true);
		if (error)
			return error;
	}

	return 0;
}