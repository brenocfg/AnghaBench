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
struct inode {int i_nlink; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  enum cp_reason_type { ____Placeholder_cp_reason_type } cp_reason_type ;
struct TYPE_4__ {int /*<<< orphan*/  i_pino; } ;
struct TYPE_3__ {int active_logs; scalar_t__ fsync_mode; } ;

/* Variables and functions */
 int CP_FASTBOOT_MODE ; 
 int CP_HARDLINK ; 
 int CP_NODE_NEED_CP ; 
 int CP_NON_REGULAR ; 
 int CP_NO_NEEDED ; 
 int CP_NO_SPC_ROLL ; 
 int CP_RECOVER_DIR ; 
 int CP_SB_NEED_CP ; 
 int CP_SPEC_LOG_NUM ; 
 int CP_WRONG_PINO ; 
 TYPE_2__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 TYPE_1__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  FASTBOOT ; 
 scalar_t__ FSYNC_MODE_STRICT ; 
 int /*<<< orphan*/  SBI_NEED_CP ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANS_DIR_INO ; 
 scalar_t__ f2fs_exist_written_data (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_is_checkpointed_node (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_need_dentry_mark (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_space_for_roll_forward (struct f2fs_sb_info*) ; 
 scalar_t__ file_wrong_pino (struct inode*) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum cp_reason_type need_do_checkpoint(struct inode *inode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	enum cp_reason_type cp_reason = CP_NO_NEEDED;

	if (!S_ISREG(inode->i_mode))
		cp_reason = CP_NON_REGULAR;
	else if (inode->i_nlink != 1)
		cp_reason = CP_HARDLINK;
	else if (is_sbi_flag_set(sbi, SBI_NEED_CP))
		cp_reason = CP_SB_NEED_CP;
	else if (file_wrong_pino(inode))
		cp_reason = CP_WRONG_PINO;
	else if (!f2fs_space_for_roll_forward(sbi))
		cp_reason = CP_NO_SPC_ROLL;
	else if (!f2fs_is_checkpointed_node(sbi, F2FS_I(inode)->i_pino))
		cp_reason = CP_NODE_NEED_CP;
	else if (test_opt(sbi, FASTBOOT))
		cp_reason = CP_FASTBOOT_MODE;
	else if (F2FS_OPTION(sbi).active_logs == 2)
		cp_reason = CP_SPEC_LOG_NUM;
	else if (F2FS_OPTION(sbi).fsync_mode == FSYNC_MODE_STRICT &&
		f2fs_need_dentry_mark(sbi, inode->i_ino) &&
		f2fs_exist_written_data(sbi, F2FS_I(inode)->i_pino,
							TRANS_DIR_INO))
		cp_reason = CP_RECOVER_DIR;

	return cp_reason;
}