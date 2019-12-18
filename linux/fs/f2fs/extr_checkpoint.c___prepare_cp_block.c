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
struct f2fs_nm_info {int /*<<< orphan*/  next_scan_nid; } ;
struct f2fs_checkpoint {void* next_free_nid; void* valid_inode_count; void* valid_node_count; int /*<<< orphan*/  valid_block_count; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 struct f2fs_checkpoint* F2FS_CKPT (struct f2fs_sb_info*) ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_free_nid (struct f2fs_sb_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  valid_inode_count (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  valid_node_count (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  valid_user_blocks (struct f2fs_sb_info*) ; 

__attribute__((used)) static void __prepare_cp_block(struct f2fs_sb_info *sbi)
{
	struct f2fs_checkpoint *ckpt = F2FS_CKPT(sbi);
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	nid_t last_nid = nm_i->next_scan_nid;

	next_free_nid(sbi, &last_nid);
	ckpt->valid_block_count = cpu_to_le64(valid_user_blocks(sbi));
	ckpt->valid_node_count = cpu_to_le32(valid_node_count(sbi));
	ckpt->valid_inode_count = cpu_to_le32(valid_inode_count(sbi));
	ckpt->next_free_nid = cpu_to_le32(last_nid);
}