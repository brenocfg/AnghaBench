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
struct inode {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  ino_cache_lock; struct inode* ino_cache_inode; int /*<<< orphan*/  fs_info; } ;
struct btrfs_path {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 struct inode* __lookup_free_space_inode (struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_fs_closing (int /*<<< orphan*/ ) ; 
 void* igrab (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct inode *lookup_free_ino_inode(struct btrfs_root *root,
				    struct btrfs_path *path)
{
	struct inode *inode = NULL;

	spin_lock(&root->ino_cache_lock);
	if (root->ino_cache_inode)
		inode = igrab(root->ino_cache_inode);
	spin_unlock(&root->ino_cache_lock);
	if (inode)
		return inode;

	inode = __lookup_free_space_inode(root, path, 0);
	if (IS_ERR(inode))
		return inode;

	spin_lock(&root->ino_cache_lock);
	if (!btrfs_fs_closing(root->fs_info))
		root->ino_cache_inode = igrab(inode);
	spin_unlock(&root->ino_cache_lock);

	return inode;
}