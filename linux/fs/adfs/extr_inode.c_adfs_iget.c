#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_blocksize; int s_blocksize_bits; } ;
struct object_info {int size; int /*<<< orphan*/  attr; int /*<<< orphan*/  execaddr; int /*<<< orphan*/  loadaddr; int /*<<< orphan*/  parent_id; int /*<<< orphan*/  indaddr; } ;
struct inode {int i_size; int i_blocks; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct TYPE_6__ {int mmu_private; int /*<<< orphan*/  attr; int /*<<< orphan*/  execaddr; int /*<<< orphan*/  loadaddr; int /*<<< orphan*/  parent_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_gid; int /*<<< orphan*/  s_uid; } ;
struct TYPE_4__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 TYPE_3__* ADFS_I (struct inode*) ; 
 TYPE_2__* ADFS_SB (struct super_block*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adfs_adfs2unix_time (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  adfs_aops ; 
 int /*<<< orphan*/  adfs_atts2mode (struct super_block*,struct inode*) ; 
 int /*<<< orphan*/  adfs_dir_inode_operations ; 
 int /*<<< orphan*/  adfs_dir_operations ; 
 int /*<<< orphan*/  adfs_file_inode_operations ; 
 int /*<<< orphan*/  adfs_file_operations ; 
 int /*<<< orphan*/  inode_fake_hash (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

struct inode *
adfs_iget(struct super_block *sb, struct object_info *obj)
{
	struct inode *inode;

	inode = new_inode(sb);
	if (!inode)
		goto out;

	inode->i_uid	 = ADFS_SB(sb)->s_uid;
	inode->i_gid	 = ADFS_SB(sb)->s_gid;
	inode->i_ino	 = obj->indaddr;
	inode->i_size	 = obj->size;
	set_nlink(inode, 2);
	inode->i_blocks	 = (inode->i_size + sb->s_blocksize - 1) >>
			    sb->s_blocksize_bits;

	/*
	 * we need to save the parent directory ID so that
	 * write_inode can update the directory information
	 * for this file.  This will need special handling
	 * for cross-directory renames.
	 */
	ADFS_I(inode)->parent_id = obj->parent_id;
	ADFS_I(inode)->loadaddr  = obj->loadaddr;
	ADFS_I(inode)->execaddr  = obj->execaddr;
	ADFS_I(inode)->attr      = obj->attr;

	inode->i_mode	 = adfs_atts2mode(sb, inode);
	adfs_adfs2unix_time(&inode->i_mtime, inode);
	inode->i_atime = inode->i_mtime;
	inode->i_ctime = inode->i_mtime;

	if (S_ISDIR(inode->i_mode)) {
		inode->i_op	= &adfs_dir_inode_operations;
		inode->i_fop	= &adfs_dir_operations;
	} else if (S_ISREG(inode->i_mode)) {
		inode->i_op	= &adfs_file_inode_operations;
		inode->i_fop	= &adfs_file_operations;
		inode->i_mapping->a_ops = &adfs_aops;
		ADFS_I(inode)->mmu_private = inode->i_size;
	}

	inode_fake_hash(inode);

out:
	return inode;
}