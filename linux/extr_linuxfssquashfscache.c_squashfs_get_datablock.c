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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {struct squashfs_sb_info* s_fs_info; } ;
struct squashfs_sb_info {int /*<<< orphan*/  read_page; } ;
struct squashfs_cache_entry {int dummy; } ;

/* Variables and functions */
 struct squashfs_cache_entry* squashfs_cache_get (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct squashfs_cache_entry *squashfs_get_datablock(struct super_block *sb,
				u64 start_block, int length)
{
	struct squashfs_sb_info *msblk = sb->s_fs_info;

	return squashfs_cache_get(sb, msblk->read_page, start_block, length);
}