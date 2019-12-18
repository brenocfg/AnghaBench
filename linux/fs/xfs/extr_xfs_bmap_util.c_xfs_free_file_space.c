#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_off_t ;
typedef  scalar_t__ xfs_fileoff_t ;
struct xfs_mount {int dummy; } ;
struct xfs_inode {struct xfs_mount* i_mount; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLONG_MAX ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_1__* VFS_I (struct xfs_inode*) ; 
 scalar_t__ XFS_B_TO_FSB (struct xfs_mount*,scalar_t__) ; 
 scalar_t__ XFS_B_TO_FSBT (struct xfs_mount*,scalar_t__) ; 
 scalar_t__ XFS_ISIZE (struct xfs_inode*) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iomap_zero_range (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ offset_in_page (scalar_t__) ; 
 int /*<<< orphan*/  round_down (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_free_file_space (struct xfs_inode*) ; 
 int xfs_flush_unmap_range (struct xfs_inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xfs_iomap_ops ; 
 int xfs_qm_dqattach (struct xfs_inode*) ; 
 int xfs_unmap_extent (struct xfs_inode*,scalar_t__,scalar_t__,int*) ; 

int
xfs_free_file_space(
	struct xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		len)
{
	struct xfs_mount	*mp = ip->i_mount;
	xfs_fileoff_t		startoffset_fsb;
	xfs_fileoff_t		endoffset_fsb;
	int			done = 0, error;

	trace_xfs_free_file_space(ip);

	error = xfs_qm_dqattach(ip);
	if (error)
		return error;

	if (len <= 0)	/* if nothing being freed */
		return 0;

	error = xfs_flush_unmap_range(ip, offset, len);
	if (error)
		return error;

	startoffset_fsb = XFS_B_TO_FSB(mp, offset);
	endoffset_fsb = XFS_B_TO_FSBT(mp, offset + len);

	/*
	 * Need to zero the stuff we're not freeing, on disk.
	 */
	if (endoffset_fsb > startoffset_fsb) {
		while (!done) {
			error = xfs_unmap_extent(ip, startoffset_fsb,
					endoffset_fsb - startoffset_fsb, &done);
			if (error)
				return error;
		}
	}

	/*
	 * Now that we've unmap all full blocks we'll have to zero out any
	 * partial block at the beginning and/or end.  iomap_zero_range is smart
	 * enough to skip any holes, including those we just created, but we
	 * must take care not to zero beyond EOF and enlarge i_size.
	 */
	if (offset >= XFS_ISIZE(ip))
		return 0;
	if (offset + len > XFS_ISIZE(ip))
		len = XFS_ISIZE(ip) - offset;
	error = iomap_zero_range(VFS_I(ip), offset, len, NULL, &xfs_iomap_ops);
	if (error)
		return error;

	/*
	 * If we zeroed right up to EOF and EOF straddles a page boundary we
	 * must make sure that the post-EOF area is also zeroed because the
	 * page could be mmap'd and iomap_zero_range doesn't do that for us.
	 * Writeback of the eof page will do this, albeit clumsily.
	 */
	if (offset + len >= XFS_ISIZE(ip) && offset_in_page(offset + len) > 0) {
		error = filemap_write_and_wait_range(VFS_I(ip)->i_mapping,
				round_down(offset + len, PAGE_SIZE), LLONG_MAX);
	}

	return error;
}