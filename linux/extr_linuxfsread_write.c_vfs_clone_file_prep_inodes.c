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
typedef  scalar_t__ u64 ;
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mode; TYPE_1__* i_sb; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,scalar_t__) ; 
 int EBADE ; 
 int EINVAL ; 
 int EISDIR ; 
 int EPERM ; 
 int ETXTBSY ; 
 int /*<<< orphan*/  IS_ALIGNED (scalar_t__,scalar_t__) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 scalar_t__ IS_SWAPFILE (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 int vfs_dedupe_file_range_compare (struct inode*,scalar_t__,struct inode*,scalar_t__,scalar_t__,int*) ; 

int vfs_clone_file_prep_inodes(struct inode *inode_in, loff_t pos_in,
			       struct inode *inode_out, loff_t pos_out,
			       u64 *len, bool is_dedupe)
{
	loff_t bs = inode_out->i_sb->s_blocksize;
	loff_t blen;
	loff_t isize;
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

	/* Are we going all the way to the end? */
	isize = i_size_read(inode_in);
	if (isize == 0)
		return 0;

	/* Zero length dedupe exits immediately; reflink goes to EOF. */
	if (*len == 0) {
		if (is_dedupe || pos_in == isize)
			return 0;
		if (pos_in > isize)
			return -EINVAL;
		*len = isize - pos_in;
	}

	/* Ensure offsets don't wrap and the input is inside i_size */
	if (pos_in + *len < pos_in || pos_out + *len < pos_out ||
	    pos_in + *len > isize)
		return -EINVAL;

	/* Don't allow dedupe past EOF in the dest file */
	if (is_dedupe) {
		loff_t	disize;

		disize = i_size_read(inode_out);
		if (pos_out >= disize || pos_out + *len > disize)
			return -EINVAL;
	}

	/* If we're linking to EOF, continue to the block boundary. */
	if (pos_in + *len == isize)
		blen = ALIGN(isize, bs) - pos_in;
	else
		blen = *len;

	/* Only reflink if we're aligned to block boundaries */
	if (!IS_ALIGNED(pos_in, bs) || !IS_ALIGNED(pos_in + blen, bs) ||
	    !IS_ALIGNED(pos_out, bs) || !IS_ALIGNED(pos_out + blen, bs))
		return -EINVAL;

	/* Don't allow overlapped reflink within the same file */
	if (same_inode) {
		if (pos_out + blen > pos_in && pos_out < pos_in + blen)
			return -EINVAL;
	}

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
	if (is_dedupe) {
		bool		is_same = false;

		ret = vfs_dedupe_file_range_compare(inode_in, pos_in,
				inode_out, pos_out, *len, &is_same);
		if (ret)
			return ret;
		if (!is_same)
			return -EBADE;
	}

	return 1;
}