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
struct ubifs_info {int dummy; } ;
struct fsck_data {int /*<<< orphan*/  inodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_ROOT ; 
 int check_inodes (struct ubifs_info*,struct fsck_data*) ; 
 int /*<<< orphan*/  check_leaf ; 
 int /*<<< orphan*/  dbg_is_chk_fs (struct ubifs_info*) ; 
 int dbg_walk_index (struct ubifs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct fsck_data*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  free_inodes (struct fsck_data*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int) ; 

int dbg_check_filesystem(struct ubifs_info *c)
{
	int err;
	struct fsck_data fsckd;

	if (!dbg_is_chk_fs(c))
		return 0;

	fsckd.inodes = RB_ROOT;
	err = dbg_walk_index(c, check_leaf, NULL, &fsckd);
	if (err)
		goto out_free;

	err = check_inodes(c, &fsckd);
	if (err)
		goto out_free;

	free_inodes(&fsckd);
	return 0;

out_free:
	ubifs_err(c, "file-system check failed with error %d", err);
	dump_stack();
	free_inodes(&fsckd);
	return err;
}