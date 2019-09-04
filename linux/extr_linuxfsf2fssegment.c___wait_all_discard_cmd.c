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
struct discard_policy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPOLICY_FSTRIM ; 
 int /*<<< orphan*/  DPOLICY_UMOUNT ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  __init_discard_policy (struct f2fs_sb_info*,struct discard_policy*,int /*<<< orphan*/ ,int) ; 
 unsigned int __wait_discard_cmd_range (struct f2fs_sb_info*,struct discard_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int __wait_all_discard_cmd(struct f2fs_sb_info *sbi,
						struct discard_policy *dpolicy)
{
	struct discard_policy dp;
	unsigned int discard_blks;

	if (dpolicy)
		return __wait_discard_cmd_range(sbi, dpolicy, 0, UINT_MAX);

	/* wait all */
	__init_discard_policy(sbi, &dp, DPOLICY_FSTRIM, 1);
	discard_blks = __wait_discard_cmd_range(sbi, &dp, 0, UINT_MAX);
	__init_discard_policy(sbi, &dp, DPOLICY_UMOUNT, 1);
	discard_blks += __wait_discard_cmd_range(sbi, &dp, 0, UINT_MAX);

	return discard_blks;
}