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
typedef  scalar_t__ xfs_off_t ;
typedef  int uint ;
struct TYPE_2__ {int sb_blocklog; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_inode {struct xfs_mount* i_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BMAPI_PREALLOC ; 
 scalar_t__ round_down (scalar_t__,int) ; 
 scalar_t__ round_up (scalar_t__,int) ; 
 int /*<<< orphan*/  trace_xfs_zero_file_space (struct xfs_inode*) ; 
 int xfs_alloc_file_space (struct xfs_inode*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int xfs_free_file_space (struct xfs_inode*,scalar_t__,scalar_t__) ; 
 scalar_t__ xfs_is_always_cow_inode (struct xfs_inode*) ; 

int
xfs_zero_file_space(
	struct xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		len)
{
	struct xfs_mount	*mp = ip->i_mount;
	uint			blksize;
	int			error;

	trace_xfs_zero_file_space(ip);

	blksize = 1 << mp->m_sb.sb_blocklog;

	/*
	 * Punch a hole and prealloc the range. We use hole punch rather than
	 * unwritten extent conversion for two reasons:
	 *
	 * 1.) Hole punch handles partial block zeroing for us.
	 *
	 * 2.) If prealloc returns ENOSPC, the file range is still zero-valued
	 * by virtue of the hole punch.
	 */
	error = xfs_free_file_space(ip, offset, len);
	if (error || xfs_is_always_cow_inode(ip))
		return error;

	return xfs_alloc_file_space(ip, round_down(offset, blksize),
				     round_up(offset + len, blksize) -
				     round_down(offset, blksize),
				     XFS_BMAPI_PREALLOC);
}