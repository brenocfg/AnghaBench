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
struct super_block {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  F2FS_SB (struct super_block*) ; 
 int /*<<< orphan*/  SBI_IS_DIRTY ; 
 int /*<<< orphan*/  f2fs_cp_error (int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_readonly (struct super_block*) ; 
 scalar_t__ is_sbi_flag_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_freeze(struct super_block *sb)
{
	if (f2fs_readonly(sb))
		return 0;

	/* IO error happened before */
	if (unlikely(f2fs_cp_error(F2FS_SB(sb))))
		return -EIO;

	/* must be clean, since sync_filesystem() was already called */
	if (is_sbi_flag_set(F2FS_SB(sb), SBI_IS_DIRTY))
		return -EINVAL;
	return 0;
}