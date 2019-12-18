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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt; } ;
struct file {int f_mode; TYPE_1__ f_path; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 int FMODE_NOWAIT ; 
 int FMODE_WRITE ; 
 int dquot_file_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  ext4_forced_shutdown (int /*<<< orphan*/ ) ; 
 int ext4_inode_attach_jinode (struct inode*) ; 
 int ext4_sample_last_mounted (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fscrypt_file_open (struct inode*,struct file*) ; 
 int fsverity_file_open (struct inode*,struct file*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_file_open(struct inode * inode, struct file * filp)
{
	int ret;

	if (unlikely(ext4_forced_shutdown(EXT4_SB(inode->i_sb))))
		return -EIO;

	ret = ext4_sample_last_mounted(inode->i_sb, filp->f_path.mnt);
	if (ret)
		return ret;

	ret = fscrypt_file_open(inode, filp);
	if (ret)
		return ret;

	ret = fsverity_file_open(inode, filp);
	if (ret)
		return ret;

	/*
	 * Set up the jbd2_inode if we are opening the inode for
	 * writing and the journal is present
	 */
	if (filp->f_mode & FMODE_WRITE) {
		ret = ext4_inode_attach_jinode(inode);
		if (ret < 0)
			return ret;
	}

	filp->f_mode |= FMODE_NOWAIT;
	return dquot_file_open(inode, filp);
}