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
struct ext2_sb_info {int /*<<< orphan*/  s_resgid; int /*<<< orphan*/  s_resuid; TYPE_1__* s_es; int /*<<< orphan*/  s_freeblocks_counter; } ;
typedef  scalar_t__ ext2_fsblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_r_blocks_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 scalar_t__ gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_group_p (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ percpu_counter_read_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext2_has_free_blocks(struct ext2_sb_info *sbi)
{
	ext2_fsblk_t free_blocks, root_blocks;

	free_blocks = percpu_counter_read_positive(&sbi->s_freeblocks_counter);
	root_blocks = le32_to_cpu(sbi->s_es->s_r_blocks_count);
	if (free_blocks < root_blocks + 1 && !capable(CAP_SYS_RESOURCE) &&
		!uid_eq(sbi->s_resuid, current_fsuid()) &&
		(gid_eq(sbi->s_resgid, GLOBAL_ROOT_GID) ||
		 !in_group_p (sbi->s_resgid))) {
		return 0;
	}
	return 1;
}