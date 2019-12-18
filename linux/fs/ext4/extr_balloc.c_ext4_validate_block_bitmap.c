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
struct super_block {int dummy; } ;
struct ext4_group_info {int dummy; } ;
struct ext4_group_desc {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;

/* Variables and functions */
 int EFSBADCRC ; 
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  EXT4_GROUP_INFO_BBITMAP_CORRUPT ; 
 scalar_t__ EXT4_MB_GRP_BBITMAP_CORRUPT (struct ext4_group_info*) ; 
 scalar_t__ buffer_verified (struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_block_bitmap_csum_verify (struct super_block*,int /*<<< orphan*/ ,struct ext4_group_desc*,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,int /*<<< orphan*/ ,...) ; 
 struct ext4_group_info* ext4_get_group_info (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_lock_group (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_mark_group_bitmap_corrupted (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_unlock_group (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_valid_block_bitmap (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_verified (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ext4_validate_block_bitmap(struct super_block *sb,
				      struct ext4_group_desc *desc,
				      ext4_group_t block_group,
				      struct buffer_head *bh)
{
	ext4_fsblk_t	blk;
	struct ext4_group_info *grp = ext4_get_group_info(sb, block_group);

	if (buffer_verified(bh))
		return 0;
	if (EXT4_MB_GRP_BBITMAP_CORRUPT(grp))
		return -EFSCORRUPTED;

	ext4_lock_group(sb, block_group);
	if (buffer_verified(bh))
		goto verified;
	if (unlikely(!ext4_block_bitmap_csum_verify(sb, block_group,
			desc, bh))) {
		ext4_unlock_group(sb, block_group);
		ext4_error(sb, "bg %u: bad block bitmap checksum", block_group);
		ext4_mark_group_bitmap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
		return -EFSBADCRC;
	}
	blk = ext4_valid_block_bitmap(sb, desc, block_group, bh);
	if (unlikely(blk != 0)) {
		ext4_unlock_group(sb, block_group);
		ext4_error(sb, "bg %u: block %llu: invalid block bitmap",
			   block_group, blk);
		ext4_mark_group_bitmap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
		return -EFSCORRUPTED;
	}
	set_buffer_verified(bh);
verified:
	ext4_unlock_group(sb, block_group);
	return 0;
}