#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct ext2_group_desc {int /*<<< orphan*/  bg_used_dirs_count; int /*<<< orphan*/  bg_free_inodes_count; } ;
struct buffer_head {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_dirs_counter; } ;

/* Variables and functions */
 TYPE_1__* EXT2_SB (struct super_block*) ; 
 int /*<<< orphan*/  ext2_error (struct super_block*,char*,char*,int) ; 
 struct ext2_group_desc* ext2_get_group_desc (struct super_block*,int,struct buffer_head**) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  percpu_counter_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_bgl_lock (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext2_release_inode(struct super_block *sb, int group, int dir)
{
	struct ext2_group_desc * desc;
	struct buffer_head *bh;

	desc = ext2_get_group_desc(sb, group, &bh);
	if (!desc) {
		ext2_error(sb, "ext2_release_inode",
			"can't get descriptor for group %d", group);
		return;
	}

	spin_lock(sb_bgl_lock(EXT2_SB(sb), group));
	le16_add_cpu(&desc->bg_free_inodes_count, 1);
	if (dir)
		le16_add_cpu(&desc->bg_used_dirs_count, -1);
	spin_unlock(sb_bgl_lock(EXT2_SB(sb), group));
	if (dir)
		percpu_counter_dec(&EXT2_SB(sb)->s_dirs_counter);
	mark_buffer_dirty(bh);
}