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
struct super_block {scalar_t__ s_fs_info; } ;
struct ecryptfs_sb_info {struct super_block* wsi_sb; } ;

/* Variables and functions */

__attribute__((used)) static inline struct super_block *
ecryptfs_superblock_to_lower(struct super_block *sb)
{
	return ((struct ecryptfs_sb_info *)sb->s_fs_info)->wsi_sb;
}