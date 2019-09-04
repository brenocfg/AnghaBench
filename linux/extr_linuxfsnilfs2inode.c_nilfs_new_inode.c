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
typedef  int /*<<< orphan*/  umode_t ;
struct the_nilfs {int /*<<< orphan*/  ns_next_gen_lock; int /*<<< orphan*/  ns_next_generation; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;
struct nilfs_root {int /*<<< orphan*/  inodes_count; int /*<<< orphan*/  ifile; } ;
struct nilfs_inode_info {int i_flags; scalar_t__ i_dir_start_lookup; int /*<<< orphan*/  i_state; int /*<<< orphan*/  i_bmap; int /*<<< orphan*/  i_bh; struct nilfs_root* i_root; } ;
struct inode {scalar_t__ i_generation; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mapping; struct super_block* i_sb; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int NILFS_FL_INHERITED ; 
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  NILFS_I_BMAP ; 
 int /*<<< orphan*/  NILFS_I_NEW ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GFP_FS ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mapping_gfp_constraint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* new_inode (struct super_block*) ; 
 int nilfs_bmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nilfs_ifile_create_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nilfs_init_acl (struct inode*,struct inode*) ; 
 scalar_t__ nilfs_insert_inode_locked (struct inode*,struct nilfs_root*,int /*<<< orphan*/ ) ; 
 int nilfs_mask_flags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nilfs_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *nilfs_new_inode(struct inode *dir, umode_t mode)
{
	struct super_block *sb = dir->i_sb;
	struct the_nilfs *nilfs = sb->s_fs_info;
	struct inode *inode;
	struct nilfs_inode_info *ii;
	struct nilfs_root *root;
	int err = -ENOMEM;
	ino_t ino;

	inode = new_inode(sb);
	if (unlikely(!inode))
		goto failed;

	mapping_set_gfp_mask(inode->i_mapping,
			   mapping_gfp_constraint(inode->i_mapping, ~__GFP_FS));

	root = NILFS_I(dir)->i_root;
	ii = NILFS_I(inode);
	ii->i_state = BIT(NILFS_I_NEW);
	ii->i_root = root;

	err = nilfs_ifile_create_inode(root->ifile, &ino, &ii->i_bh);
	if (unlikely(err))
		goto failed_ifile_create_inode;
	/* reference count of i_bh inherits from nilfs_mdt_read_block() */

	atomic64_inc(&root->inodes_count);
	inode_init_owner(inode, dir, mode);
	inode->i_ino = ino;
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);

	if (S_ISREG(mode) || S_ISDIR(mode) || S_ISLNK(mode)) {
		err = nilfs_bmap_read(ii->i_bmap, NULL);
		if (err < 0)
			goto failed_after_creation;

		set_bit(NILFS_I_BMAP, &ii->i_state);
		/* No lock is needed; iget() ensures it. */
	}

	ii->i_flags = nilfs_mask_flags(
		mode, NILFS_I(dir)->i_flags & NILFS_FL_INHERITED);

	/* ii->i_file_acl = 0; */
	/* ii->i_dir_acl = 0; */
	ii->i_dir_start_lookup = 0;
	nilfs_set_inode_flags(inode);
	spin_lock(&nilfs->ns_next_gen_lock);
	inode->i_generation = nilfs->ns_next_generation++;
	spin_unlock(&nilfs->ns_next_gen_lock);
	if (nilfs_insert_inode_locked(inode, root, ino) < 0) {
		err = -EIO;
		goto failed_after_creation;
	}

	err = nilfs_init_acl(inode, dir);
	if (unlikely(err))
		/*
		 * Never occur.  When supporting nilfs_init_acl(),
		 * proper cancellation of above jobs should be considered.
		 */
		goto failed_after_creation;

	return inode;

 failed_after_creation:
	clear_nlink(inode);
	unlock_new_inode(inode);
	iput(inode);  /*
		       * raw_inode will be deleted through
		       * nilfs_evict_inode().
		       */
	goto failed;

 failed_ifile_create_inode:
	make_bad_inode(inode);
	iput(inode);
 failed:
	return ERR_PTR(err);
}