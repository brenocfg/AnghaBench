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
struct timespec64 {int dummy; } ;
struct super_block {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * a_ops; } ;
struct inode {int i_state; int i_mode; int i_ino; int i_size; int i_blocks; struct timespec64 i_ctime; struct timespec64 i_atime; struct timespec64 i_mtime; TYPE_1__ i_data; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; } ;
struct cramfs_inode {int mode; int size; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  linear_phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CRAMFS_MTD ; 
 int CRAMFS_FLAG_EXT_BLOCK_POINTERS ; 
 TYPE_2__* CRAMFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int I_NEW ; 
#define  S_IFDIR 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  cramfs_aops ; 
 int /*<<< orphan*/  cramfs_dir_inode_operations ; 
 int /*<<< orphan*/  cramfs_directory_operations ; 
 int /*<<< orphan*/  cramfs_physmem_fops ; 
 int /*<<< orphan*/  cramino (struct cramfs_inode const*,unsigned int) ; 
 int /*<<< orphan*/  generic_ro_fops ; 
 int /*<<< orphan*/  i_gid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,int /*<<< orphan*/ ) ; 
 struct inode* iget_locked (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 int /*<<< orphan*/  old_decode_dev (int) ; 
 int /*<<< orphan*/  page_symlink_inode_operations ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static struct inode *get_cramfs_inode(struct super_block *sb,
	const struct cramfs_inode *cramfs_inode, unsigned int offset)
{
	struct inode *inode;
	static struct timespec64 zerotime;

	inode = iget_locked(sb, cramino(cramfs_inode, offset));
	if (!inode)
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;

	switch (cramfs_inode->mode & S_IFMT) {
	case S_IFREG:
		inode->i_fop = &generic_ro_fops;
		inode->i_data.a_ops = &cramfs_aops;
		if (IS_ENABLED(CONFIG_CRAMFS_MTD) &&
		    CRAMFS_SB(sb)->flags & CRAMFS_FLAG_EXT_BLOCK_POINTERS &&
		    CRAMFS_SB(sb)->linear_phys_addr)
			inode->i_fop = &cramfs_physmem_fops;
		break;
	case S_IFDIR:
		inode->i_op = &cramfs_dir_inode_operations;
		inode->i_fop = &cramfs_directory_operations;
		break;
	case S_IFLNK:
		inode->i_op = &page_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_data.a_ops = &cramfs_aops;
		break;
	default:
		init_special_inode(inode, cramfs_inode->mode,
				old_decode_dev(cramfs_inode->size));
	}

	inode->i_mode = cramfs_inode->mode;
	i_uid_write(inode, cramfs_inode->uid);
	i_gid_write(inode, cramfs_inode->gid);

	/* if the lower 2 bits are zero, the inode contains data */
	if (!(inode->i_ino & 3)) {
		inode->i_size = cramfs_inode->size;
		inode->i_blocks = (cramfs_inode->size - 1) / 512 + 1;
	}

	/* Struct copy intentional */
	inode->i_mtime = inode->i_atime = inode->i_ctime = zerotime;
	/* inode->i_nlink is left 1 - arguably wrong for directories,
	   but it's the best we can do without reading the directory
	   contents.  1 yields the right result in GNU find, even
	   without -noleaf option. */

	unlock_new_inode(inode);

	return inode;
}