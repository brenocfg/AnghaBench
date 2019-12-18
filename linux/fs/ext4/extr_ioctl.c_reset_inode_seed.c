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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_ino; } ;
struct ext4_sb_info {void* s_csum_seed; } ;
struct ext4_inode_info {void* i_csum_seed; } ;
typedef  int /*<<< orphan*/  inum ;
typedef  int /*<<< orphan*/  gen ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  void* __u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* ext4_chksum (struct ext4_sb_info*,void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ext4_has_metadata_csum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_inode_seed(struct inode *inode)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	__le32 inum = cpu_to_le32(inode->i_ino);
	__le32 gen = cpu_to_le32(inode->i_generation);
	__u32 csum;

	if (!ext4_has_metadata_csum(inode->i_sb))
		return;

	csum = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)&inum, sizeof(inum));
	ei->i_csum_seed = ext4_chksum(sbi, csum, (__u8 *)&gen, sizeof(gen));
}