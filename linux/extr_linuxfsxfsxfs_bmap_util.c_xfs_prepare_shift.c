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
struct xfs_inode {int dummy; } ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLFILEOFF ; 
 int PAGE_SHIFT ; 
 TYPE_1__* VFS_I (struct xfs_inode*) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,int,int) ; 
 int invalidate_inode_pages2_range (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ xfs_can_free_eofblocks (struct xfs_inode*,int) ; 
 int xfs_free_eofblocks (struct xfs_inode*) ; 
 scalar_t__ xfs_inode_has_cow_data (struct xfs_inode*) ; 
 int xfs_reflink_cancel_cow_range (struct xfs_inode*,int,int /*<<< orphan*/ ,int) ; 

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
	error = filemap_write_and_wait_range(VFS_I(ip)->i_mapping, offset, -1);
	if (error)
		return error;
	error = invalidate_inode_pages2_range(VFS_I(ip)->i_mapping,
					offset >> PAGE_SHIFT, -1);
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