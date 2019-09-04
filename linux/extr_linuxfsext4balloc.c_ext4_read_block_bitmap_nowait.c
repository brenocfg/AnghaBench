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
struct super_block {int dummy; } ;
struct ext4_sb_info {TYPE_1__* s_es; } ;
struct ext4_group_desc {int bg_flags; } ;
struct buffer_head {int /*<<< orphan*/  b_end_io; } ;
typedef  scalar_t__ ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_first_data_block; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int ENOMEM ; 
 struct buffer_head* ERR_PTR (int) ; 
 int /*<<< orphan*/  EXT4_BG_BLOCK_UNINIT ; 
 int /*<<< orphan*/  EXT4_GROUP_INFO_BBITMAP_CORRUPT ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int REQ_PRIO ; 
 scalar_t__ bitmap_uptodate (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_block_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ext4_blocks_count (TYPE_1__*) ; 
 int /*<<< orphan*/  ext4_end_bitmap_read ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,...) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_has_group_desc_csum (struct super_block*) ; 
 int ext4_init_block_bitmap (struct super_block*,struct buffer_head*,scalar_t__,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_lock_group (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  ext4_mark_group_bitmap_corrupted (struct super_block*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_unlock_group (struct super_block*,scalar_t__) ; 
 int ext4_validate_block_bitmap (struct super_block*,struct ext4_group_desc*,scalar_t__,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_warning (struct super_block*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 struct buffer_head* sb_getblk (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  set_bitmap_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_verified (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,int,struct buffer_head*) ; 
 int /*<<< orphan*/  trace_ext4_read_block_bitmap_load (struct super_block*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

struct buffer_head *
ext4_read_block_bitmap_nowait(struct super_block *sb, ext4_group_t block_group)
{
	struct ext4_group_desc *desc;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct buffer_head *bh;
	ext4_fsblk_t bitmap_blk;
	int err;

	desc = ext4_get_group_desc(sb, block_group, NULL);
	if (!desc)
		return ERR_PTR(-EFSCORRUPTED);
	bitmap_blk = ext4_block_bitmap(sb, desc);
	if ((bitmap_blk <= le32_to_cpu(sbi->s_es->s_first_data_block)) ||
	    (bitmap_blk >= ext4_blocks_count(sbi->s_es))) {
		ext4_error(sb, "Invalid block bitmap block %llu in "
			   "block_group %u", bitmap_blk, block_group);
		ext4_mark_group_bitmap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
		return ERR_PTR(-EFSCORRUPTED);
	}
	bh = sb_getblk(sb, bitmap_blk);
	if (unlikely(!bh)) {
		ext4_warning(sb, "Cannot get buffer for block bitmap - "
			     "block_group = %u, block_bitmap = %llu",
			     block_group, bitmap_blk);
		return ERR_PTR(-ENOMEM);
	}

	if (bitmap_uptodate(bh))
		goto verify;

	lock_buffer(bh);
	if (bitmap_uptodate(bh)) {
		unlock_buffer(bh);
		goto verify;
	}
	ext4_lock_group(sb, block_group);
	if (ext4_has_group_desc_csum(sb) &&
	    (desc->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT))) {
		if (block_group == 0) {
			ext4_unlock_group(sb, block_group);
			unlock_buffer(bh);
			ext4_error(sb, "Block bitmap for bg 0 marked "
				   "uninitialized");
			err = -EFSCORRUPTED;
			goto out;
		}
		err = ext4_init_block_bitmap(sb, bh, block_group, desc);
		set_bitmap_uptodate(bh);
		set_buffer_uptodate(bh);
		set_buffer_verified(bh);
		ext4_unlock_group(sb, block_group);
		unlock_buffer(bh);
		if (err) {
			ext4_error(sb, "Failed to init block bitmap for group "
				   "%u: %d", block_group, err);
			goto out;
		}
		goto verify;
	}
	ext4_unlock_group(sb, block_group);
	if (buffer_uptodate(bh)) {
		/*
		 * if not uninit if bh is uptodate,
		 * bitmap is also uptodate
		 */
		set_bitmap_uptodate(bh);
		unlock_buffer(bh);
		goto verify;
	}
	/*
	 * submit the buffer_head for reading
	 */
	set_buffer_new(bh);
	trace_ext4_read_block_bitmap_load(sb, block_group);
	bh->b_end_io = ext4_end_bitmap_read;
	get_bh(bh);
	submit_bh(REQ_OP_READ, REQ_META | REQ_PRIO, bh);
	return bh;
verify:
	err = ext4_validate_block_bitmap(sb, desc, block_group, bh);
	if (err)
		goto out;
	return bh;
out:
	put_bh(bh);
	return ERR_PTR(err);
}