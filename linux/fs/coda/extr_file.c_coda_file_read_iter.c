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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct coda_file_info {int /*<<< orphan*/  cfi_access_intent; int /*<<< orphan*/  cfi_container; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_ACCESS_TYPE_READ ; 
 int /*<<< orphan*/  CODA_ACCESS_TYPE_READ_FINISH ; 
 struct coda_file_info* coda_ftoc (struct file*) ; 
 int /*<<< orphan*/  coda_i2f (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 scalar_t__ venus_access_intent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_iter_read (int /*<<< orphan*/ ,struct iov_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
coda_file_read_iter(struct kiocb *iocb, struct iov_iter *to)
{
	struct file *coda_file = iocb->ki_filp;
	struct inode *coda_inode = file_inode(coda_file);
	struct coda_file_info *cfi = coda_ftoc(coda_file);
	loff_t ki_pos = iocb->ki_pos;
	size_t count = iov_iter_count(to);
	ssize_t ret;

	ret = venus_access_intent(coda_inode->i_sb, coda_i2f(coda_inode),
				  &cfi->cfi_access_intent,
				  count, ki_pos, CODA_ACCESS_TYPE_READ);
	if (ret)
		goto finish_read;

	ret = vfs_iter_read(cfi->cfi_container, to, &iocb->ki_pos, 0);

finish_read:
	venus_access_intent(coda_inode->i_sb, coda_i2f(coda_inode),
			    &cfi->cfi_access_intent,
			    count, ki_pos, CODA_ACCESS_TYPE_READ_FINISH);
	return ret;
}