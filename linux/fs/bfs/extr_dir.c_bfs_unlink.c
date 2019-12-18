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
struct inode {scalar_t__ i_ino; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; TYPE_1__* i_sb; int /*<<< orphan*/  i_nlink; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct buffer_head {int dummy; } ;
struct bfs_sb_info {int /*<<< orphan*/  bfs_lock; } ;
struct bfs_dirent {scalar_t__ ino; } ;
struct TYPE_2__ {char* s_id; } ;

/* Variables and functions */
 struct bfs_sb_info* BFS_SB (TYPE_1__*) ; 
 int ENOENT ; 
 struct buffer_head* bfs_find_entry (struct inode*,int /*<<< orphan*/ *,struct bfs_dirent**) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

__attribute__((used)) static int bfs_unlink(struct inode *dir, struct dentry *dentry)
{
	int error = -ENOENT;
	struct inode *inode = d_inode(dentry);
	struct buffer_head *bh;
	struct bfs_dirent *de;
	struct bfs_sb_info *info = BFS_SB(inode->i_sb);

	mutex_lock(&info->bfs_lock);
	bh = bfs_find_entry(dir, &dentry->d_name, &de);
	if (!bh || (le16_to_cpu(de->ino) != inode->i_ino))
		goto out_brelse;

	if (!inode->i_nlink) {
		printf("unlinking non-existent file %s:%lu (nlink=%d)\n",
					inode->i_sb->s_id, inode->i_ino,
					inode->i_nlink);
		set_nlink(inode, 1);
	}
	de->ino = 0;
	mark_buffer_dirty_inode(bh, dir);
	dir->i_ctime = dir->i_mtime = current_time(dir);
	mark_inode_dirty(dir);
	inode->i_ctime = dir->i_ctime;
	inode_dec_link_count(inode);
	error = 0;

out_brelse:
	brelse(bh);
	mutex_unlock(&info->bfs_lock);
	return error;
}