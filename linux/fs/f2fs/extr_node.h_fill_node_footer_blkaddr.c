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
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  next_blkaddr; int /*<<< orphan*/  cp_ver; } ;
struct f2fs_node {TYPE_1__ footer; } ;
struct f2fs_checkpoint {int dummy; } ;
typedef  int /*<<< orphan*/  block_t ;
typedef  int __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CP_CRC_RECOVERY_FLAG ; 
 struct f2fs_checkpoint* F2FS_CKPT (int /*<<< orphan*/ ) ; 
 struct f2fs_node* F2FS_NODE (struct page*) ; 
 int /*<<< orphan*/  F2FS_P_SB (struct page*) ; 
 scalar_t__ __is_set_ckpt_flags (struct f2fs_checkpoint*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int cur_cp_crc (struct f2fs_checkpoint*) ; 
 int cur_cp_version (struct f2fs_checkpoint*) ; 

__attribute__((used)) static inline void fill_node_footer_blkaddr(struct page *page, block_t blkaddr)
{
	struct f2fs_checkpoint *ckpt = F2FS_CKPT(F2FS_P_SB(page));
	struct f2fs_node *rn = F2FS_NODE(page);
	__u64 cp_ver = cur_cp_version(ckpt);

	if (__is_set_ckpt_flags(ckpt, CP_CRC_RECOVERY_FLAG))
		cp_ver |= (cur_cp_crc(ckpt) << 32);

	rn->footer.cp_ver = cpu_to_le64(cp_ver);
	rn->footer.next_blkaddr = cpu_to_le32(blkaddr);
}