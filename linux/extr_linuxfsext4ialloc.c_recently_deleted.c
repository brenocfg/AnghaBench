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
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct ext4_inode {int /*<<< orphan*/  i_dtime; } ;
struct ext4_group_desc {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  ext4_group_t ;
struct TYPE_2__ {int s_inodes_per_block; } ;

/* Variables and functions */
 int EXT4_INODE_SIZE (struct super_block*) ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 scalar_t__ RECENTCY_DIRTY ; 
 int RECENTCY_MIN ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_inode_table (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_find_get_block (struct super_block*,scalar_t__) ; 
 scalar_t__ time_before32 (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int recently_deleted(struct super_block *sb, ext4_group_t group, int ino)
{
	struct ext4_group_desc	*gdp;
	struct ext4_inode	*raw_inode;
	struct buffer_head	*bh;
	int inodes_per_block = EXT4_SB(sb)->s_inodes_per_block;
	int offset, ret = 0;
	int recentcy = RECENTCY_MIN;
	u32 dtime, now;

	gdp = ext4_get_group_desc(sb, group, NULL);
	if (unlikely(!gdp))
		return 0;

	bh = sb_find_get_block(sb, ext4_inode_table(sb, gdp) +
		       (ino / inodes_per_block));
	if (!bh || !buffer_uptodate(bh))
		/*
		 * If the block is not in the buffer cache, then it
		 * must have been written out.
		 */
		goto out;

	offset = (ino % inodes_per_block) * EXT4_INODE_SIZE(sb);
	raw_inode = (struct ext4_inode *) (bh->b_data + offset);

	/* i_dtime is only 32 bits on disk, but we only care about relative
	 * times in the range of a few minutes (i.e. long enough to sync a
	 * recently-deleted inode to disk), so using the low 32 bits of the
	 * clock (a 68 year range) is enough, see time_before32() */
	dtime = le32_to_cpu(raw_inode->i_dtime);
	now = ktime_get_real_seconds();
	if (buffer_dirty(bh))
		recentcy += RECENTCY_DIRTY;

	if (dtime && time_before32(dtime, now) &&
	    time_before32(now, dtime + recentcy))
		ret = 1;
out:
	brelse(bh);
	return ret;
}