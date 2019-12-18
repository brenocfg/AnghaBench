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
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mode; } ;
struct file {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EBADE ; 
 int EINVAL ; 
 int EISDIR ; 
 int EPERM ; 
 int ETXTBSY ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 scalar_t__ IS_SWAPFILE (struct inode*) ; 
 unsigned int REMAP_FILE_DEDUP ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int file_modified (struct file*) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int generic_remap_check_len (struct inode*,struct inode*,scalar_t__,scalar_t__*,unsigned int) ; 
 int generic_remap_checks (struct file*,scalar_t__,struct file*,scalar_t__,scalar_t__*,unsigned int) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 int vfs_dedupe_file_range_compare (struct inode*,scalar_t__,struct inode*,scalar_t__,scalar_t__,int*) ; 

int generic_remap_file_range_prep(struct file *file_in, loff_t pos_in,
				  struct file *file_out, loff_t pos_out,
				  loff_t *len, unsigned int remap_flags)
{
	struct inode *inode_in = file_inode(file_in);
	struct inode *inode_out = file_inode(file_out);
	bool same_inode = (inode_in == inode_out);
	int ret;

	/* Don't touch certain kinds of inodes */
	if (IS_IMMUTABLE(inode_out))
		return -EPERM;

	if (IS_SWAPFILE(inode_in) || IS_SWAPFILE(inode_out))
		return -ETXTBSY;

	/* Don't reflink dirs, pipes, sockets... */
	if (S_ISDIR(inode_in->i_mode) || S_ISDIR(inode_out->i_mode))
		return -EISDIR;
	if (!S_ISREG(inode_in->i_mode) || !S_ISREG(inode_out->i_mode))
		return -EINVAL;

	/* Zero length dedupe exits immediately; reflink goes to EOF. */
	if (*len == 0) {
		loff_t isize = i_size_read(inode_in);

		if ((remap_flags & REMAP_FILE_DEDUP) || pos_in == isize)
			return 0;
		if (pos_in > isize)
			return -EINVAL;
		*len = isize - pos_in;
		if (*len == 0)
			return 0;
	}

	/* Check that we don't violate system file offset limits. */
	ret = generic_remap_checks(file_in, pos_in, file_out, pos_out, len,
			remap_flags);
	if (ret)
		return ret;

	/* Wait for the completion of any pending IOs on both files */
	inode_dio_wait(inode_in);
	if (!same_inode)
		inode_dio_wait(inode_out);

	ret = filemap_write_and_wait_range(inode_in->i_mapping,
			pos_in, pos_in + *len - 1);
	if (ret)
		return ret;

	ret = filemap_write_and_wait_range(inode_out->i_mapping,
			pos_out, pos_out + *len - 1);
	if (ret)
		return ret;

	/*
	 * Check that the extents are the same.
	 */
	if (remap_flags & REMAP_FILE_DEDUP) {
		bool		is_same = false;

		ret = vfs_dedupe_file_range_compare(inode_in, pos_in,
				inode_out, pos_out, *len, &is_same);
		if (ret)
			return ret;
		if (!is_same)
			return -EBADE;
	}

	ret = generic_remap_check_len(inode_in, inode_out, pos_out, len,
			remap_flags);
	if (ret)
		return ret;

	/* If can't alter the file contents, we're done. */
	if (!(remap_flags & REMAP_FILE_DEDUP))
		ret = file_modified(file_out);

	return ret;
}