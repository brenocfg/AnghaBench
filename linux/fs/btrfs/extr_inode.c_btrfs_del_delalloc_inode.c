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
struct btrfs_root {int /*<<< orphan*/  delalloc_lock; } ;
struct btrfs_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __btrfs_del_delalloc_inode (struct btrfs_root*,struct btrfs_inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfs_del_delalloc_inode(struct btrfs_root *root,
				     struct btrfs_inode *inode)
{
	spin_lock(&root->delalloc_lock);
	__btrfs_del_delalloc_inode(root, inode);
	spin_unlock(&root->delalloc_lock);
}