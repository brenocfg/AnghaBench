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
struct ecryptfs_sb_info {int /*<<< orphan*/  mount_crypt_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecryptfs_destroy_mount_crypt_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecryptfs_sb_info_cache ; 
 struct ecryptfs_sb_info* ecryptfs_superblock_to_private (struct super_block*) ; 
 int /*<<< orphan*/  kill_anon_super (struct super_block*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ecryptfs_sb_info*) ; 

__attribute__((used)) static void ecryptfs_kill_block_super(struct super_block *sb)
{
	struct ecryptfs_sb_info *sb_info = ecryptfs_superblock_to_private(sb);
	kill_anon_super(sb);
	if (!sb_info)
		return;
	ecryptfs_destroy_mount_crypt_stat(&sb_info->mount_crypt_stat);
	kmem_cache_free(ecryptfs_sb_info_cache, sb_info);
}