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
struct xfs_inode {int /*<<< orphan*/  i_mount; int /*<<< orphan*/  i_pincount; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__* VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_STATS_DEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_active ; 
 int /*<<< orphan*/  xfs_inode_free_callback ; 

__attribute__((used)) static void
__xfs_inode_free(
	struct xfs_inode	*ip)
{
	/* asserts to verify all state is correct here */
	ASSERT(atomic_read(&ip->i_pincount) == 0);
	XFS_STATS_DEC(ip->i_mount, vn_active);

	call_rcu(&VFS_I(ip)->i_rcu, xfs_inode_free_callback);
}