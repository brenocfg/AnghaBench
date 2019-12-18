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
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  VFS_I (struct xfs_inode*) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 
 int iomap_zero_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_zero_eof (struct xfs_inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xfs_iomap_ops ; 

__attribute__((used)) static int
xfs_reflink_zero_posteof(
	struct xfs_inode	*ip,
	loff_t			pos)
{
	loff_t			isize = i_size_read(VFS_I(ip));

	if (pos <= isize)
		return 0;

	trace_xfs_zero_eof(ip, isize, pos - isize);
	return iomap_zero_range(VFS_I(ip), isize, pos - isize, NULL,
			&xfs_iomap_ops);
}