#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct super_block {int dummy; } ;
struct inode {unsigned long i_ino; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; scalar_t__ i_blocks; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; struct super_block* i_sb; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct bfs_sb_info {int si_lasti; int /*<<< orphan*/  bfs_lock; int /*<<< orphan*/  si_freei; int /*<<< orphan*/  si_imap; } ;
struct TYPE_4__ {unsigned long i_dsk_ino; scalar_t__ i_eblock; scalar_t__ i_sblock; } ;
struct TYPE_3__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 TYPE_2__* BFS_I (struct inode*) ; 
 struct bfs_sb_info* BFS_SB (struct super_block*) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int bfs_add_entry (struct inode*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  bfs_aops ; 
 int /*<<< orphan*/  bfs_dump_imap (char*,struct super_block*) ; 
 int /*<<< orphan*/  bfs_file_inops ; 
 int /*<<< orphan*/  bfs_file_operations ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 unsigned long find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bfs_create(struct inode *dir, struct dentry *dentry, umode_t mode,
						bool excl)
{
	int err;
	struct inode *inode;
	struct super_block *s = dir->i_sb;
	struct bfs_sb_info *info = BFS_SB(s);
	unsigned long ino;

	inode = new_inode(s);
	if (!inode)
		return -ENOMEM;
	mutex_lock(&info->bfs_lock);
	ino = find_first_zero_bit(info->si_imap, info->si_lasti + 1);
	if (ino > info->si_lasti) {
		mutex_unlock(&info->bfs_lock);
		iput(inode);
		return -ENOSPC;
	}
	set_bit(ino, info->si_imap);
	info->si_freei--;
	inode_init_owner(inode, dir, mode);
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	inode->i_blocks = 0;
	inode->i_op = &bfs_file_inops;
	inode->i_fop = &bfs_file_operations;
	inode->i_mapping->a_ops = &bfs_aops;
	inode->i_ino = ino;
	BFS_I(inode)->i_dsk_ino = ino;
	BFS_I(inode)->i_sblock = 0;
	BFS_I(inode)->i_eblock = 0;
	insert_inode_hash(inode);
        mark_inode_dirty(inode);
	bfs_dump_imap("create", s);

	err = bfs_add_entry(dir, &dentry->d_name, inode->i_ino);
	if (err) {
		inode_dec_link_count(inode);
		mutex_unlock(&info->bfs_lock);
		iput(inode);
		return err;
	}
	mutex_unlock(&info->bfs_lock);
	d_instantiate(dentry, inode);
	return 0;
}