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
struct super_block {struct squashfs_sb_info* s_fs_info; } ;
struct squashfs_sb_info {struct squashfs_sb_info* xattr_id_table; struct squashfs_sb_info* inode_lookup_table; struct squashfs_sb_info* meta_index; struct squashfs_sb_info* fragment_index; struct squashfs_sb_info* id_table; int /*<<< orphan*/  read_page; int /*<<< orphan*/  fragment_cache; int /*<<< orphan*/  block_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct squashfs_sb_info*) ; 
 int /*<<< orphan*/  squashfs_cache_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  squashfs_decompressor_destroy (struct squashfs_sb_info*) ; 

__attribute__((used)) static void squashfs_put_super(struct super_block *sb)
{
	if (sb->s_fs_info) {
		struct squashfs_sb_info *sbi = sb->s_fs_info;
		squashfs_cache_delete(sbi->block_cache);
		squashfs_cache_delete(sbi->fragment_cache);
		squashfs_cache_delete(sbi->read_page);
		squashfs_decompressor_destroy(sbi);
		kfree(sbi->id_table);
		kfree(sbi->fragment_index);
		kfree(sbi->meta_index);
		kfree(sbi->inode_lookup_table);
		kfree(sbi->xattr_id_table);
		kfree(sb->s_fs_info);
		sb->s_fs_info = NULL;
	}
}