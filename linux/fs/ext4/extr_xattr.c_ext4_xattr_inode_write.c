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
struct inode {int i_blkbits; TYPE_1__* i_sb; } ;
struct ext4_map_blocks {unsigned long m_lblk; int m_len; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int ENOSPC ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*) ; 
 int /*<<< orphan*/  EXT4_GET_BLOCKS_CREATE ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct buffer_head* ext4_getblk (int /*<<< orphan*/ *,struct inode*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_handle_dirty_metadata (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ext4_map_blocks (int /*<<< orphan*/ *,struct inode*,struct ext4_map_blocks*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_should_retry_alloc (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  ext4_update_i_disksize (struct inode*,int) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 

__attribute__((used)) static int ext4_xattr_inode_write(handle_t *handle, struct inode *ea_inode,
				  const void *buf, int bufsize)
{
	struct buffer_head *bh = NULL;
	unsigned long block = 0;
	int blocksize = ea_inode->i_sb->s_blocksize;
	int max_blocks = (bufsize + blocksize - 1) >> ea_inode->i_blkbits;
	int csize, wsize = 0;
	int ret = 0;
	int retries = 0;

retry:
	while (ret >= 0 && ret < max_blocks) {
		struct ext4_map_blocks map;
		map.m_lblk = block += ret;
		map.m_len = max_blocks -= ret;

		ret = ext4_map_blocks(handle, ea_inode, &map,
				      EXT4_GET_BLOCKS_CREATE);
		if (ret <= 0) {
			ext4_mark_inode_dirty(handle, ea_inode);
			if (ret == -ENOSPC &&
			    ext4_should_retry_alloc(ea_inode->i_sb, &retries)) {
				ret = 0;
				goto retry;
			}
			break;
		}
	}

	if (ret < 0)
		return ret;

	block = 0;
	while (wsize < bufsize) {
		if (bh != NULL)
			brelse(bh);
		csize = (bufsize - wsize) > blocksize ? blocksize :
								bufsize - wsize;
		bh = ext4_getblk(handle, ea_inode, block, 0);
		if (IS_ERR(bh))
			return PTR_ERR(bh);
		if (!bh) {
			WARN_ON_ONCE(1);
			EXT4_ERROR_INODE(ea_inode,
					 "ext4_getblk() return bh = NULL");
			return -EFSCORRUPTED;
		}
		ret = ext4_journal_get_write_access(handle, bh);
		if (ret)
			goto out;

		memcpy(bh->b_data, buf, csize);
		set_buffer_uptodate(bh);
		ext4_handle_dirty_metadata(handle, ea_inode, bh);

		buf += csize;
		wsize += csize;
		block += 1;
	}

	inode_lock(ea_inode);
	i_size_write(ea_inode, wsize);
	ext4_update_i_disksize(ea_inode, wsize);
	inode_unlock(ea_inode);

	ext4_mark_inode_dirty(handle, ea_inode);

out:
	brelse(bh);

	return ret;
}