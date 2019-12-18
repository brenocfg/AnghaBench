#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {int i_ino; struct super_block* i_sb; } ;
struct ext4_iloc {int block_group; int offset; struct buffer_head* bh; } ;
struct ext4_group_desc {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_end_io; int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; } ;
struct blk_plug {int dummy; } ;
typedef  unsigned int ext4_fsblk_t ;
typedef  unsigned int __u32 ;
struct TYPE_4__ {int s_inodes_per_block; unsigned int s_inode_readahead_blks; TYPE_1__* s_es; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_inodes_count; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE_BLOCK (struct inode*,unsigned int,char*) ; 
 int EXT4_INODES_PER_GROUP (struct super_block*) ; 
 int EXT4_INODE_SIZE (struct super_block*) ; 
 int EXT4_ROOT_INO ; 
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int REQ_PRIO ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ buffer_write_io_error (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_has_group_desc_csum (struct super_block*) ; 
 unsigned int ext4_inode_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 unsigned int ext4_inode_table (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ext4_itable_unused_count (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ext4_test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_breadahead (struct super_block*,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,int,struct buffer_head*) ; 
 int /*<<< orphan*/  trace_ext4_load_inode (struct inode*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

__attribute__((used)) static int __ext4_get_inode_loc(struct inode *inode,
				struct ext4_iloc *iloc, int in_mem)
{
	struct ext4_group_desc	*gdp;
	struct buffer_head	*bh;
	struct super_block	*sb = inode->i_sb;
	ext4_fsblk_t		block;
	struct blk_plug		plug;
	int			inodes_per_block, inode_offset;

	iloc->bh = NULL;
	if (inode->i_ino < EXT4_ROOT_INO ||
	    inode->i_ino > le32_to_cpu(EXT4_SB(sb)->s_es->s_inodes_count))
		return -EFSCORRUPTED;

	iloc->block_group = (inode->i_ino - 1) / EXT4_INODES_PER_GROUP(sb);
	gdp = ext4_get_group_desc(sb, iloc->block_group, NULL);
	if (!gdp)
		return -EIO;

	/*
	 * Figure out the offset within the block group inode table
	 */
	inodes_per_block = EXT4_SB(sb)->s_inodes_per_block;
	inode_offset = ((inode->i_ino - 1) %
			EXT4_INODES_PER_GROUP(sb));
	block = ext4_inode_table(sb, gdp) + (inode_offset / inodes_per_block);
	iloc->offset = (inode_offset % inodes_per_block) * EXT4_INODE_SIZE(sb);

	bh = sb_getblk(sb, block);
	if (unlikely(!bh))
		return -ENOMEM;
	if (!buffer_uptodate(bh)) {
		lock_buffer(bh);

		/*
		 * If the buffer has the write error flag, we have failed
		 * to write out another inode in the same block.  In this
		 * case, we don't have to read the block because we may
		 * read the old inode data successfully.
		 */
		if (buffer_write_io_error(bh) && !buffer_uptodate(bh))
			set_buffer_uptodate(bh);

		if (buffer_uptodate(bh)) {
			/* someone brought it uptodate while we waited */
			unlock_buffer(bh);
			goto has_buffer;
		}

		/*
		 * If we have all information of the inode in memory and this
		 * is the only valid inode in the block, we need not read the
		 * block.
		 */
		if (in_mem) {
			struct buffer_head *bitmap_bh;
			int i, start;

			start = inode_offset & ~(inodes_per_block - 1);

			/* Is the inode bitmap in cache? */
			bitmap_bh = sb_getblk(sb, ext4_inode_bitmap(sb, gdp));
			if (unlikely(!bitmap_bh))
				goto make_io;

			/*
			 * If the inode bitmap isn't in cache then the
			 * optimisation may end up performing two reads instead
			 * of one, so skip it.
			 */
			if (!buffer_uptodate(bitmap_bh)) {
				brelse(bitmap_bh);
				goto make_io;
			}
			for (i = start; i < start + inodes_per_block; i++) {
				if (i == inode_offset)
					continue;
				if (ext4_test_bit(i, bitmap_bh->b_data))
					break;
			}
			brelse(bitmap_bh);
			if (i == start + inodes_per_block) {
				/* all other inodes are free, so skip I/O */
				memset(bh->b_data, 0, bh->b_size);
				set_buffer_uptodate(bh);
				unlock_buffer(bh);
				goto has_buffer;
			}
		}

make_io:
		/*
		 * If we need to do any I/O, try to pre-readahead extra
		 * blocks from the inode table.
		 */
		blk_start_plug(&plug);
		if (EXT4_SB(sb)->s_inode_readahead_blks) {
			ext4_fsblk_t b, end, table;
			unsigned num;
			__u32 ra_blks = EXT4_SB(sb)->s_inode_readahead_blks;

			table = ext4_inode_table(sb, gdp);
			/* s_inode_readahead_blks is always a power of 2 */
			b = block & ~((ext4_fsblk_t) ra_blks - 1);
			if (table > b)
				b = table;
			end = b + ra_blks;
			num = EXT4_INODES_PER_GROUP(sb);
			if (ext4_has_group_desc_csum(sb))
				num -= ext4_itable_unused_count(sb, gdp);
			table += num / inodes_per_block;
			if (end > table)
				end = table;
			while (b <= end)
				sb_breadahead(sb, b++);
		}

		/*
		 * There are other valid inodes in the buffer, this inode
		 * has in-inode xattrs, or we don't have this inode in memory.
		 * Read the block from disk.
		 */
		trace_ext4_load_inode(inode);
		get_bh(bh);
		bh->b_end_io = end_buffer_read_sync;
		submit_bh(REQ_OP_READ, REQ_META | REQ_PRIO, bh);
		blk_finish_plug(&plug);
		wait_on_buffer(bh);
		if (!buffer_uptodate(bh)) {
			EXT4_ERROR_INODE_BLOCK(inode, block,
					       "unable to read itable block");
			brelse(bh);
			return -EIO;
		}
	}
has_buffer:
	iloc->bh = bh;
	return 0;
}