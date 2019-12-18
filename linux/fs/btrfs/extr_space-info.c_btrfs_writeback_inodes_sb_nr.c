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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {int /*<<< orphan*/  s_umount; } ;
struct btrfs_fs_info {struct super_block* sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  WB_REASON_FS_FREE_SPACE ; 
 int /*<<< orphan*/  btrfs_start_delalloc_roots (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  btrfs_wait_ordered_roots (struct btrfs_fs_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 scalar_t__ down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeback_inodes_sb_nr (struct super_block*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btrfs_writeback_inodes_sb_nr(struct btrfs_fs_info *fs_info,
					 unsigned long nr_pages, int nr_items)
{
	struct super_block *sb = fs_info->sb;

	if (down_read_trylock(&sb->s_umount)) {
		writeback_inodes_sb_nr(sb, nr_pages, WB_REASON_FS_FREE_SPACE);
		up_read(&sb->s_umount);
	} else {
		/*
		 * We needn't worry the filesystem going from r/w to r/o though
		 * we don't acquire ->s_umount mutex, because the filesystem
		 * should guarantee the delalloc inodes list be empty after
		 * the filesystem is readonly(all dirty pages are written to
		 * the disk).
		 */
		btrfs_start_delalloc_roots(fs_info, nr_items);
		if (!current->journal_info)
			btrfs_wait_ordered_roots(fs_info, nr_items, 0, (u64)-1);
	}
}