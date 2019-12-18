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
struct inode {int i_blkbits; int i_size; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; } ;
struct file {int dummy; } ;
struct ext4_map_blocks {scalar_t__ m_lblk; scalar_t__ m_len; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_lblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSPC ; 
 int EXT4_GET_BLOCKS_NO_NORMALIZE ; 
 int /*<<< orphan*/  EXT4_HT_MAP_BLOCKS ; 
 int /*<<< orphan*/  EXT4_INODE_EOFBLOCKS ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 scalar_t__ EXT_UNWRITTEN_MAX_LEN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 unsigned int ext4_chunk_trans_blocks (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  ext4_debug (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,unsigned int) ; 
 int ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int ext4_map_blocks (int /*<<< orphan*/ *,struct inode*,struct ext4_map_blocks*,int) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int) ; 
 int ext4_update_inode_size (struct inode*,int) ; 
 int ext_depth (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 

__attribute__((used)) static int ext4_alloc_file_blocks(struct file *file, ext4_lblk_t offset,
				  ext4_lblk_t len, loff_t new_size,
				  int flags)
{
	struct inode *inode = file_inode(file);
	handle_t *handle;
	int ret = 0;
	int ret2 = 0;
	int retries = 0;
	int depth = 0;
	struct ext4_map_blocks map;
	unsigned int credits;
	loff_t epos;

	BUG_ON(!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS));
	map.m_lblk = offset;
	map.m_len = len;
	/*
	 * Don't normalize the request if it can fit in one extent so
	 * that it doesn't get unnecessarily split into multiple
	 * extents.
	 */
	if (len <= EXT_UNWRITTEN_MAX_LEN)
		flags |= EXT4_GET_BLOCKS_NO_NORMALIZE;

	/*
	 * credits to insert 1 extent into extent tree
	 */
	credits = ext4_chunk_trans_blocks(inode, len);
	depth = ext_depth(inode);

retry:
	while (ret >= 0 && len) {
		/*
		 * Recalculate credits when extent tree depth changes.
		 */
		if (depth != ext_depth(inode)) {
			credits = ext4_chunk_trans_blocks(inode, len);
			depth = ext_depth(inode);
		}

		handle = ext4_journal_start(inode, EXT4_HT_MAP_BLOCKS,
					    credits);
		if (IS_ERR(handle)) {
			ret = PTR_ERR(handle);
			break;
		}
		ret = ext4_map_blocks(handle, inode, &map, flags);
		if (ret <= 0) {
			ext4_debug("inode #%lu: block %u: len %u: "
				   "ext4_ext_map_blocks returned %d",
				   inode->i_ino, map.m_lblk,
				   map.m_len, ret);
			ext4_mark_inode_dirty(handle, inode);
			ret2 = ext4_journal_stop(handle);
			break;
		}
		map.m_lblk += ret;
		map.m_len = len = len - ret;
		epos = (loff_t)map.m_lblk << inode->i_blkbits;
		inode->i_ctime = current_time(inode);
		if (new_size) {
			if (epos > new_size)
				epos = new_size;
			if (ext4_update_inode_size(inode, epos) & 0x1)
				inode->i_mtime = inode->i_ctime;
		} else {
			if (epos > inode->i_size)
				ext4_set_inode_flag(inode,
						    EXT4_INODE_EOFBLOCKS);
		}
		ext4_mark_inode_dirty(handle, inode);
		ext4_update_inode_fsync_trans(handle, inode, 1);
		ret2 = ext4_journal_stop(handle);
		if (ret2)
			break;
	}
	if (ret == -ENOSPC &&
			ext4_should_retry_alloc(inode->i_sb, &retries)) {
		ret = 0;
		goto retry;
	}

	return ret > 0 ? ret2 : ret;
}