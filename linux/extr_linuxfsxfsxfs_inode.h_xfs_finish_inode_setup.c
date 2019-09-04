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
struct xfs_inode {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_INEW ; 
 int /*<<< orphan*/  __XFS_INEW_BIT ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  unlock_new_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iflags_clear (struct xfs_inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void xfs_finish_inode_setup(struct xfs_inode *ip)
{
	xfs_iflags_clear(ip, XFS_INEW);
	barrier();
	unlock_new_inode(VFS_I(ip));
	wake_up_bit(&ip->i_flags, __XFS_INEW_BIT);
}