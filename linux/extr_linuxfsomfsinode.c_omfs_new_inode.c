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
typedef  int umode_t ;
typedef  int /*<<< orphan*/  u64 ;
struct omfs_sb_info {int /*<<< orphan*/  s_sys_blocksize; int /*<<< orphan*/  s_mirrors; } ;
struct inode {int /*<<< orphan*/  i_size; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; TYPE_1__* i_mapping; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 struct omfs_sb_info* OMFS_SB (int /*<<< orphan*/ ) ; 
#define  S_IFDIR 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 int omfs_allocate_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  omfs_aops ; 
 int /*<<< orphan*/  omfs_dir_inops ; 
 int /*<<< orphan*/  omfs_dir_operations ; 
 int /*<<< orphan*/  omfs_file_inops ; 
 int /*<<< orphan*/  omfs_file_operations ; 

struct inode *omfs_new_inode(struct inode *dir, umode_t mode)
{
	struct inode *inode;
	u64 new_block;
	int err;
	int len;
	struct omfs_sb_info *sbi = OMFS_SB(dir->i_sb);

	inode = new_inode(dir->i_sb);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	err = omfs_allocate_range(dir->i_sb, sbi->s_mirrors, sbi->s_mirrors,
			&new_block, &len);
	if (err)
		goto fail;

	inode->i_ino = new_block;
	inode_init_owner(inode, NULL, mode);
	inode->i_mapping->a_ops = &omfs_aops;

	inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
	switch (mode & S_IFMT) {
	case S_IFDIR:
		inode->i_op = &omfs_dir_inops;
		inode->i_fop = &omfs_dir_operations;
		inode->i_size = sbi->s_sys_blocksize;
		inc_nlink(inode);
		break;
	case S_IFREG:
		inode->i_op = &omfs_file_inops;
		inode->i_fop = &omfs_file_operations;
		inode->i_size = 0;
		break;
	}

	insert_inode_hash(inode);
	mark_inode_dirty(inode);
	return inode;
fail:
	make_bad_inode(inode);
	iput(inode);
	return ERR_PTR(err);
}