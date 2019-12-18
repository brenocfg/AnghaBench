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
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct bfs_sb_info {int /*<<< orphan*/  bfs_lock; } ;

/* Variables and functions */
 struct bfs_sb_info* BFS_SB (int /*<<< orphan*/ ) ; 
 int bfs_add_entry (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bfs_link(struct dentry *old, struct inode *dir,
						struct dentry *new)
{
	struct inode *inode = d_inode(old);
	struct bfs_sb_info *info = BFS_SB(inode->i_sb);
	int err;

	mutex_lock(&info->bfs_lock);
	err = bfs_add_entry(dir, &new->d_name, inode->i_ino);
	if (err) {
		mutex_unlock(&info->bfs_lock);
		return err;
	}
	inc_nlink(inode);
	inode->i_ctime = current_time(inode);
	mark_inode_dirty(inode);
	ihold(inode);
	d_instantiate(new, inode);
	mutex_unlock(&info->bfs_lock);
	return 0;
}