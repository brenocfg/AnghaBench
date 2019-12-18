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
struct ext4_group_desc {int dummy; } ;
struct buffer_head {scalar_t__ b_blocknr; } ;
typedef  int /*<<< orphan*/  ext4_group_t ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int EIO ; 
 int /*<<< orphan*/  EXT4_GROUP_INFO_BBITMAP_CORRUPT ; 
 int /*<<< orphan*/  buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_group_bitmap_corrupted (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext4_validate_block_bitmap (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

int ext4_wait_block_bitmap(struct super_block *sb, ext4_group_t block_group,
			   struct buffer_head *bh)
{
	struct ext4_group_desc *desc;

	if (!buffer_new(bh))
		return 0;
	desc = ext4_get_group_desc(sb, block_group, NULL);
	if (!desc)
		return -EFSCORRUPTED;
	wait_on_buffer(bh);
	if (!buffer_uptodate(bh)) {
		ext4_error(sb, "Cannot read block bitmap - "
			   "block_group = %u, block_bitmap = %llu",
			   block_group, (unsigned long long) bh->b_blocknr);
		ext4_mark_group_bitmap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
		return -EIO;
	}
	clear_buffer_new(bh);
	/* Panic or remount fs read-only if block bitmap is invalid */
	return ext4_validate_block_bitmap(sb, desc, block_group, bh);
}