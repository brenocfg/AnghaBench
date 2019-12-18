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
struct inode {int i_blkbits; scalar_t__ i_sb; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; } ;
struct file {int dummy; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {size_t p_depth; struct ext4_extent* p_ext; } ;
typedef  int pgoff_t ;
typedef  int ext4_lblk_t ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int EOPNOTSUPP ; 
 int EXT_MAX_BLOCKS ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_discard_preallocations (struct inode*) ; 
 int /*<<< orphan*/  ext4_double_down_write_data_sem (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  ext4_double_up_write_data_sem (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int ext4_ext_is_unwritten (struct ext4_extent*) ; 
 int ext4_ext_next_allocated_block (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_msg (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int get_ext_path (struct inode*,int,struct ext4_ext_path**) ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_two_nondirectories (struct inode*,struct inode*) ; 
 int mext_check_arguments (struct inode*,struct inode*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  move_extent_per_page (struct file*,struct inode*,int,int,int,int,int,int*) ; 
 int /*<<< orphan*/  unlock_two_nondirectories (struct inode*,struct inode*) ; 

int
ext4_move_extents(struct file *o_filp, struct file *d_filp, __u64 orig_blk,
		  __u64 donor_blk, __u64 len, __u64 *moved_len)
{
	struct inode *orig_inode = file_inode(o_filp);
	struct inode *donor_inode = file_inode(d_filp);
	struct ext4_ext_path *path = NULL;
	int blocks_per_page = PAGE_SIZE >> orig_inode->i_blkbits;
	ext4_lblk_t o_end, o_start = orig_blk;
	ext4_lblk_t d_start = donor_blk;
	int ret;

	if (orig_inode->i_sb != donor_inode->i_sb) {
		ext4_debug("ext4 move extent: The argument files "
			"should be in same FS [ino:orig %lu, donor %lu]\n",
			orig_inode->i_ino, donor_inode->i_ino);
		return -EINVAL;
	}

	/* orig and donor should be different inodes */
	if (orig_inode == donor_inode) {
		ext4_debug("ext4 move extent: The argument files should not "
			"be same inode [ino:orig %lu, donor %lu]\n",
			orig_inode->i_ino, donor_inode->i_ino);
		return -EINVAL;
	}

	/* Regular file check */
	if (!S_ISREG(orig_inode->i_mode) || !S_ISREG(donor_inode->i_mode)) {
		ext4_debug("ext4 move extent: The argument files should be "
			"regular file [ino:orig %lu, donor %lu]\n",
			orig_inode->i_ino, donor_inode->i_ino);
		return -EINVAL;
	}

	/* TODO: it's not obvious how to swap blocks for inodes with full
	   journaling enabled */
	if (ext4_should_journal_data(orig_inode) ||
	    ext4_should_journal_data(donor_inode)) {
		ext4_msg(orig_inode->i_sb, KERN_ERR,
			 "Online defrag not supported with data journaling");
		return -EOPNOTSUPP;
	}

	if (IS_ENCRYPTED(orig_inode) || IS_ENCRYPTED(donor_inode)) {
		ext4_msg(orig_inode->i_sb, KERN_ERR,
			 "Online defrag not supported for encrypted files");
		return -EOPNOTSUPP;
	}

	/* Protect orig and donor inodes against a truncate */
	lock_two_nondirectories(orig_inode, donor_inode);

	/* Wait for all existing dio workers */
	inode_dio_wait(orig_inode);
	inode_dio_wait(donor_inode);

	/* Protect extent tree against block allocations via delalloc */
	ext4_double_down_write_data_sem(orig_inode, donor_inode);
	/* Check the filesystem environment whether move_extent can be done */
	ret = mext_check_arguments(orig_inode, donor_inode, orig_blk,
				    donor_blk, &len);
	if (ret)
		goto out;
	o_end = o_start + len;

	while (o_start < o_end) {
		struct ext4_extent *ex;
		ext4_lblk_t cur_blk, next_blk;
		pgoff_t orig_page_index, donor_page_index;
		int offset_in_page;
		int unwritten, cur_len;

		ret = get_ext_path(orig_inode, o_start, &path);
		if (ret)
			goto out;
		ex = path[path->p_depth].p_ext;
		next_blk = ext4_ext_next_allocated_block(path);
		cur_blk = le32_to_cpu(ex->ee_block);
		cur_len = ext4_ext_get_actual_len(ex);
		/* Check hole before the start pos */
		if (cur_blk + cur_len - 1 < o_start) {
			if (next_blk == EXT_MAX_BLOCKS) {
				o_start = o_end;
				ret = -ENODATA;
				goto out;
			}
			d_start += next_blk - o_start;
			o_start = next_blk;
			continue;
		/* Check hole after the start pos */
		} else if (cur_blk > o_start) {
			/* Skip hole */
			d_start += cur_blk - o_start;
			o_start = cur_blk;
			/* Extent inside requested range ?*/
			if (cur_blk >= o_end)
				goto out;
		} else { /* in_range(o_start, o_blk, o_len) */
			cur_len += cur_blk - o_start;
		}
		unwritten = ext4_ext_is_unwritten(ex);
		if (o_end - o_start < cur_len)
			cur_len = o_end - o_start;

		orig_page_index = o_start >> (PAGE_SHIFT -
					       orig_inode->i_blkbits);
		donor_page_index = d_start >> (PAGE_SHIFT -
					       donor_inode->i_blkbits);
		offset_in_page = o_start % blocks_per_page;
		if (cur_len > blocks_per_page- offset_in_page)
			cur_len = blocks_per_page - offset_in_page;
		/*
		 * Up semaphore to avoid following problems:
		 * a. transaction deadlock among ext4_journal_start,
		 *    ->write_begin via pagefault, and jbd2_journal_commit
		 * b. racing with ->readpage, ->write_begin, and ext4_get_block
		 *    in move_extent_per_page
		 */
		ext4_double_up_write_data_sem(orig_inode, donor_inode);
		/* Swap original branches with new branches */
		move_extent_per_page(o_filp, donor_inode,
				     orig_page_index, donor_page_index,
				     offset_in_page, cur_len,
				     unwritten, &ret);
		ext4_double_down_write_data_sem(orig_inode, donor_inode);
		if (ret < 0)
			break;
		o_start += cur_len;
		d_start += cur_len;
	}
	*moved_len = o_start - orig_blk;
	if (*moved_len > len)
		*moved_len = len;

out:
	if (*moved_len) {
		ext4_discard_preallocations(orig_inode);
		ext4_discard_preallocations(donor_inode);
	}

	ext4_ext_drop_refs(path);
	kfree(path);
	ext4_double_up_write_data_sem(orig_inode, donor_inode);
	unlock_two_nondirectories(orig_inode, donor_inode);

	return ret;
}