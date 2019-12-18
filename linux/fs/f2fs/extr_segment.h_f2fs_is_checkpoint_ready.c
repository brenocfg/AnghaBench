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
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 int /*<<< orphan*/  has_not_enough_free_secs (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline bool f2fs_is_checkpoint_ready(struct f2fs_sb_info *sbi)
{
	if (likely(!is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		return true;
	if (likely(!has_not_enough_free_secs(sbi, 0, 0)))
		return true;
	return false;
}