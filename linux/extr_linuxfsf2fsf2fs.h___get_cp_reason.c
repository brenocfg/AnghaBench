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

/* Variables and functions */
 int CP_FASTBOOT ; 
 int CP_SYNC ; 
 int CP_UMOUNT ; 
 int /*<<< orphan*/  FASTBOOT ; 
 int /*<<< orphan*/  SBI_IS_CLOSE ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __get_cp_reason(struct f2fs_sb_info *sbi)
{
	int reason = CP_SYNC;

	if (test_opt(sbi, FASTBOOT))
		reason = CP_FASTBOOT;
	if (is_sbi_flag_set(sbi, SBI_IS_CLOSE))
		reason = CP_UMOUNT;
	return reason;
}