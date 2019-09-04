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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_sb_info {scalar_t__ s_cluster_ratio; } ;
typedef  scalar_t__ ext4_lblk_t ;

/* Variables and functions */
 scalar_t__ EXT4_LBLK_CMASK (struct ext4_sb_info*,scalar_t__) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 int ext4_find_delalloc_range (struct inode*,scalar_t__,scalar_t__) ; 

int ext4_find_delalloc_cluster(struct inode *inode, ext4_lblk_t lblk)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	ext4_lblk_t lblk_start, lblk_end;
	lblk_start = EXT4_LBLK_CMASK(sbi, lblk);
	lblk_end = lblk_start + sbi->s_cluster_ratio - 1;

	return ext4_find_delalloc_range(inode, lblk_start, lblk_end);
}