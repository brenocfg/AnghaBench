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
struct btrfs_trans_handle {scalar_t__ transid; } ;
struct btrfs_root {scalar_t__ last_trans; int /*<<< orphan*/  state; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  reloc_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ROOT_IN_TRANS_SETUP ; 
 int /*<<< orphan*/  BTRFS_ROOT_REF_COWS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_root_in_trans (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_record_root_in_trans(struct btrfs_trans_handle *trans,
			       struct btrfs_root *root)
{
	struct btrfs_fs_info *fs_info = root->fs_info;

	if (!test_bit(BTRFS_ROOT_REF_COWS, &root->state))
		return 0;

	/*
	 * see record_root_in_trans for comments about IN_TRANS_SETUP usage
	 * and barriers
	 */
	smp_rmb();
	if (root->last_trans == trans->transid &&
	    !test_bit(BTRFS_ROOT_IN_TRANS_SETUP, &root->state))
		return 0;

	mutex_lock(&fs_info->reloc_mutex);
	record_root_in_trans(trans, root, 0);
	mutex_unlock(&fs_info->reloc_mutex);

	return 0;
}