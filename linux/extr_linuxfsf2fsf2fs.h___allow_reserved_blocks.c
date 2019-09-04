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
struct inode {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_resgid; int /*<<< orphan*/  s_resuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 TYPE_1__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 scalar_t__ IS_NOQUOTA (struct inode*) ; 
 int /*<<< orphan*/  RESERVE_ROOT ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ in_group_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool __allow_reserved_blocks(struct f2fs_sb_info *sbi,
					struct inode *inode, bool cap)
{
	if (!inode)
		return true;
	if (!test_opt(sbi, RESERVE_ROOT))
		return false;
	if (IS_NOQUOTA(inode))
		return true;
	if (uid_eq(F2FS_OPTION(sbi).s_resuid, current_fsuid()))
		return true;
	if (!gid_eq(F2FS_OPTION(sbi).s_resgid, GLOBAL_ROOT_GID) &&
					in_group_p(F2FS_OPTION(sbi).s_resgid))
		return true;
	if (cap && capable(CAP_SYS_RESOURCE))
		return true;
	return false;
}