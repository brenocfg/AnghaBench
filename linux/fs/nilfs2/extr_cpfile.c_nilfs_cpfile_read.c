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
struct super_block {size_t s_blocksize; } ;
struct nilfs_inode {int dummy; } ;
struct nilfs_cpfile_header {int dummy; } ;
struct inode {int i_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int I_NEW ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  NILFS_CPFILE_INO ; 
 int /*<<< orphan*/  NILFS_MDT_GFP ; 
 size_t NILFS_MIN_CHECKPOINT_SIZE ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 struct inode* nilfs_iget_locked (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nilfs_mdt_init (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_mdt_set_entry_size (struct inode*,size_t,int) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,size_t) ; 
 int nilfs_read_inode_common (struct inode*,struct nilfs_inode*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

int nilfs_cpfile_read(struct super_block *sb, size_t cpsize,
		      struct nilfs_inode *raw_inode, struct inode **inodep)
{
	struct inode *cpfile;
	int err;

	if (cpsize > sb->s_blocksize) {
		nilfs_msg(sb, KERN_ERR,
			  "too large checkpoint size: %zu bytes", cpsize);
		return -EINVAL;
	} else if (cpsize < NILFS_MIN_CHECKPOINT_SIZE) {
		nilfs_msg(sb, KERN_ERR,
			  "too small checkpoint size: %zu bytes", cpsize);
		return -EINVAL;
	}

	cpfile = nilfs_iget_locked(sb, NULL, NILFS_CPFILE_INO);
	if (unlikely(!cpfile))
		return -ENOMEM;
	if (!(cpfile->i_state & I_NEW))
		goto out;

	err = nilfs_mdt_init(cpfile, NILFS_MDT_GFP, 0);
	if (err)
		goto failed;

	nilfs_mdt_set_entry_size(cpfile, cpsize,
				 sizeof(struct nilfs_cpfile_header));

	err = nilfs_read_inode_common(cpfile, raw_inode);
	if (err)
		goto failed;

	unlock_new_inode(cpfile);
 out:
	*inodep = cpfile;
	return 0;
 failed:
	iget_failed(cpfile);
	return err;
}