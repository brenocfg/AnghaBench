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
struct f2fs_sb_info {int /*<<< orphan*/  quota_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_DIRTY_QDATA ; 
 int /*<<< orphan*/  SBI_QUOTA_NEED_FLUSH ; 
 int /*<<< orphan*/  SBI_QUOTA_NEED_REPAIR ; 
 int /*<<< orphan*/  SBI_QUOTA_SKIP_FLUSH ; 
 int /*<<< orphan*/  clear_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ get_pages (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_journalled_quota (struct f2fs_sb_info*) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __need_flush_quota(struct f2fs_sb_info *sbi)
{
	bool ret = false;

	if (!is_journalled_quota(sbi))
		return false;

	down_write(&sbi->quota_sem);
	if (is_sbi_flag_set(sbi, SBI_QUOTA_SKIP_FLUSH)) {
		ret = false;
	} else if (is_sbi_flag_set(sbi, SBI_QUOTA_NEED_REPAIR)) {
		ret = false;
	} else if (is_sbi_flag_set(sbi, SBI_QUOTA_NEED_FLUSH)) {
		clear_sbi_flag(sbi, SBI_QUOTA_NEED_FLUSH);
		ret = true;
	} else if (get_pages(sbi, F2FS_DIRTY_QDATA)) {
		ret = true;
	}
	up_write(&sbi->quota_sem);
	return ret;
}