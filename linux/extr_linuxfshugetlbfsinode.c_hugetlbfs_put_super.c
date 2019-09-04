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
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct hugetlbfs_sb_info {scalar_t__ spool; } ;

/* Variables and functions */
 struct hugetlbfs_sb_info* HUGETLBFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  hugepage_put_subpool (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct hugetlbfs_sb_info*) ; 

__attribute__((used)) static void hugetlbfs_put_super(struct super_block *sb)
{
	struct hugetlbfs_sb_info *sbi = HUGETLBFS_SB(sb);

	if (sbi) {
		sb->s_fs_info = NULL;

		if (sbi->spool)
			hugepage_put_subpool(sbi->spool);

		kfree(sbi);
	}
}