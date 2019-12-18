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
typedef  scalar_t__ uint64_t ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int EPERM ; 
 int ETXTBSY ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 scalar_t__ IS_SWAPFILE (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int generic_file_rw_checks (struct file*,struct file*) ; 
 int generic_write_check_limits (struct file*,scalar_t__,scalar_t__*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

int generic_copy_file_checks(struct file *file_in, loff_t pos_in,
			     struct file *file_out, loff_t pos_out,
			     size_t *req_count, unsigned int flags)
{
	struct inode *inode_in = file_inode(file_in);
	struct inode *inode_out = file_inode(file_out);
	uint64_t count = *req_count;
	loff_t size_in;
	int ret;

	ret = generic_file_rw_checks(file_in, file_out);
	if (ret)
		return ret;

	/* Don't touch certain kinds of inodes */
	if (IS_IMMUTABLE(inode_out))
		return -EPERM;

	if (IS_SWAPFILE(inode_in) || IS_SWAPFILE(inode_out))
		return -ETXTBSY;

	/* Ensure offsets don't wrap. */
	if (pos_in + count < pos_in || pos_out + count < pos_out)
		return -EOVERFLOW;

	/* Shorten the copy to EOF */
	size_in = i_size_read(inode_in);
	if (pos_in >= size_in)
		count = 0;
	else
		count = min(count, size_in - (uint64_t)pos_in);

	ret = generic_write_check_limits(file_out, pos_out, &count);
	if (ret)
		return ret;

	/* Don't allow overlapped copying within the same file. */
	if (inode_in == inode_out &&
	    pos_out + count > pos_in &&
	    pos_out < pos_in + count)
		return -EINVAL;

	*req_count = count;
	return 0;
}