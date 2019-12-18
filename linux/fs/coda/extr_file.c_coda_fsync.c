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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mode; } ;
struct file {int dummy; } ;
struct coda_file_info {struct file* cfi_container; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 struct coda_file_info* coda_ftoc (struct file*) ; 
 int /*<<< orphan*/  coda_i2f (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int venus_fsync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vfs_fsync (struct file*,int) ; 

int coda_fsync(struct file *coda_file, loff_t start, loff_t end, int datasync)
{
	struct file *host_file;
	struct inode *coda_inode = file_inode(coda_file);
	struct coda_file_info *cfi;
	int err;

	if (!(S_ISREG(coda_inode->i_mode) || S_ISDIR(coda_inode->i_mode) ||
	      S_ISLNK(coda_inode->i_mode)))
		return -EINVAL;

	err = filemap_write_and_wait_range(coda_inode->i_mapping, start, end);
	if (err)
		return err;
	inode_lock(coda_inode);

	cfi = coda_ftoc(coda_file);
	host_file = cfi->cfi_container;

	err = vfs_fsync(host_file, datasync);
	if (!err && !datasync)
		err = venus_fsync(coda_inode->i_sb, coda_i2f(coda_inode));
	inode_unlock(coda_inode);

	return err;
}