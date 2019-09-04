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
struct kiocb {int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int i_size; int i_blocks; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct file {int dummy; } ;
struct coda_file_info {scalar_t__ cfi_magic; struct file* cfi_container; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct coda_file_info* CODA_FTOC (struct file*) ; 
 scalar_t__ CODA_MAGIC ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  file_end_write (struct file*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  file_start_write (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  vfs_iter_write (struct file*,struct iov_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
coda_file_write_iter(struct kiocb *iocb, struct iov_iter *to)
{
	struct file *coda_file = iocb->ki_filp;
	struct inode *coda_inode = file_inode(coda_file);
	struct coda_file_info *cfi = CODA_FTOC(coda_file);
	struct file *host_file;
	ssize_t ret;

	BUG_ON(!cfi || cfi->cfi_magic != CODA_MAGIC);

	host_file = cfi->cfi_container;
	file_start_write(host_file);
	inode_lock(coda_inode);
	ret = vfs_iter_write(cfi->cfi_container, to, &iocb->ki_pos, 0);
	coda_inode->i_size = file_inode(host_file)->i_size;
	coda_inode->i_blocks = (coda_inode->i_size + 511) >> 9;
	coda_inode->i_mtime = coda_inode->i_ctime = current_time(coda_inode);
	inode_unlock(coda_inode);
	file_end_write(host_file);
	return ret;
}