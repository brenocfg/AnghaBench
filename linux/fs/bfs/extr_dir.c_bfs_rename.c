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
struct inode {scalar_t__ i_ino; void* i_ctime; void* i_mtime; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct buffer_head {int dummy; } ;
struct bfs_sb_info {int /*<<< orphan*/  bfs_lock; } ;
struct bfs_dirent {scalar_t__ ino; } ;

/* Variables and functions */
 struct bfs_sb_info* BFS_SB (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOENT ; 
 int EPERM ; 
 unsigned int RENAME_NOREPLACE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int bfs_add_entry (struct inode*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct buffer_head* bfs_find_entry (struct inode*,int /*<<< orphan*/ *,struct bfs_dirent**) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bfs_rename(struct inode *old_dir, struct dentry *old_dentry,
		      struct inode *new_dir, struct dentry *new_dentry,
		      unsigned int flags)
{
	struct inode *old_inode, *new_inode;
	struct buffer_head *old_bh, *new_bh;
	struct bfs_dirent *old_de, *new_de;
	struct bfs_sb_info *info;
	int error = -ENOENT;

	if (flags & ~RENAME_NOREPLACE)
		return -EINVAL;

	old_bh = new_bh = NULL;
	old_inode = d_inode(old_dentry);
	if (S_ISDIR(old_inode->i_mode))
		return -EINVAL;

	info = BFS_SB(old_inode->i_sb);

	mutex_lock(&info->bfs_lock);
	old_bh = bfs_find_entry(old_dir, &old_dentry->d_name, &old_de);

	if (!old_bh || (le16_to_cpu(old_de->ino) != old_inode->i_ino))
		goto end_rename;

	error = -EPERM;
	new_inode = d_inode(new_dentry);
	new_bh = bfs_find_entry(new_dir, &new_dentry->d_name, &new_de);

	if (new_bh && !new_inode) {
		brelse(new_bh);
		new_bh = NULL;
	}
	if (!new_bh) {
		error = bfs_add_entry(new_dir, &new_dentry->d_name,
					old_inode->i_ino);
		if (error)
			goto end_rename;
	}
	old_de->ino = 0;
	old_dir->i_ctime = old_dir->i_mtime = current_time(old_dir);
	mark_inode_dirty(old_dir);
	if (new_inode) {
		new_inode->i_ctime = current_time(new_inode);
		inode_dec_link_count(new_inode);
	}
	mark_buffer_dirty_inode(old_bh, old_dir);
	error = 0;

end_rename:
	mutex_unlock(&info->bfs_lock);
	brelse(old_bh);
	brelse(new_bh);
	return error;
}