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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_checkpoint {int /*<<< orphan*/  checksum_offset; } ;
typedef  int /*<<< orphan*/  chksum ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 unsigned int CP_CHKSUM_OFFSET ; 
 scalar_t__ F2FS_BLKSIZE ; 
 int /*<<< orphan*/  f2fs_chksum (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_crc32 (struct f2fs_sb_info*,struct f2fs_checkpoint*,unsigned int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __u32 f2fs_checkpoint_chksum(struct f2fs_sb_info *sbi,
						struct f2fs_checkpoint *ckpt)
{
	unsigned int chksum_ofs = le32_to_cpu(ckpt->checksum_offset);
	__u32 chksum;

	chksum = f2fs_crc32(sbi, ckpt, chksum_ofs);
	if (chksum_ofs < CP_CHKSUM_OFFSET) {
		chksum_ofs += sizeof(chksum);
		chksum = f2fs_chksum(sbi, chksum, (__u8 *)ckpt + chksum_ofs,
						F2FS_BLKSIZE - chksum_ofs);
	}
	return chksum;
}