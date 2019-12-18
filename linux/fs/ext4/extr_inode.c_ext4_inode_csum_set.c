#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_inode_info {int dummy; } ;
struct ext4_inode {void* i_checksum_hi; void* i_checksum_lo; } ;
typedef  int __u32 ;
struct TYPE_4__ {TYPE_1__* s_es; } ;
struct TYPE_3__ {scalar_t__ s_creator_os; } ;

/* Variables and functions */
 scalar_t__ EXT4_FITS_IN_INODE (struct ext4_inode*,struct ext4_inode_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ EXT4_GOOD_OLD_INODE_SIZE ; 
 scalar_t__ EXT4_INODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_OS_LINUX ; 
 TYPE_2__* EXT4_SB (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_has_metadata_csum (int /*<<< orphan*/ ) ; 
 int ext4_inode_csum (struct inode*,struct ext4_inode*,struct ext4_inode_info*) ; 
 int /*<<< orphan*/  i_checksum_hi ; 

__attribute__((used)) static void ext4_inode_csum_set(struct inode *inode, struct ext4_inode *raw,
				struct ext4_inode_info *ei)
{
	__u32 csum;

	if (EXT4_SB(inode->i_sb)->s_es->s_creator_os !=
	    cpu_to_le32(EXT4_OS_LINUX) ||
	    !ext4_has_metadata_csum(inode->i_sb))
		return;

	csum = ext4_inode_csum(inode, raw, ei);
	raw->i_checksum_lo = cpu_to_le16(csum & 0xFFFF);
	if (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE &&
	    EXT4_FITS_IN_INODE(raw, ei, i_checksum_hi))
		raw->i_checksum_hi = cpu_to_le16(csum >> 16);
}