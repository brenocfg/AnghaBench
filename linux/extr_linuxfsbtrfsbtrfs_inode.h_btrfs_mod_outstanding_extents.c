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
struct btrfs_inode {int outstanding_extents; int /*<<< orphan*/  root; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_ino (struct btrfs_inode*) ; 
 scalar_t__ btrfs_is_free_space_inode (struct btrfs_inode*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_inode_mod_outstanding_extents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void btrfs_mod_outstanding_extents(struct btrfs_inode *inode,
						 int mod)
{
	lockdep_assert_held(&inode->lock);
	inode->outstanding_extents += mod;
	if (btrfs_is_free_space_inode(inode))
		return;
	trace_btrfs_inode_mod_outstanding_extents(inode->root, btrfs_ino(inode),
						  mod);
}