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
struct btrfs_root {int qgroup_meta_rsv_prealloc; int qgroup_meta_rsv_pertrans; int /*<<< orphan*/  qgroup_meta_rsv_lock; } ;
typedef  enum btrfs_qgroup_rsv_type { ____Placeholder_btrfs_qgroup_rsv_type } btrfs_qgroup_rsv_type ;

/* Variables and functions */
 int BTRFS_QGROUP_RSV_META_PERTRANS ; 
 int BTRFS_QGROUP_RSV_META_PREALLOC ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_root_meta_rsv(struct btrfs_root *root, int num_bytes,
			      enum btrfs_qgroup_rsv_type type)
{
	if (type != BTRFS_QGROUP_RSV_META_PREALLOC &&
	    type != BTRFS_QGROUP_RSV_META_PERTRANS)
		return;
	if (num_bytes == 0)
		return;

	spin_lock(&root->qgroup_meta_rsv_lock);
	if (type == BTRFS_QGROUP_RSV_META_PREALLOC)
		root->qgroup_meta_rsv_prealloc += num_bytes;
	else
		root->qgroup_meta_rsv_pertrans += num_bytes;
	spin_unlock(&root->qgroup_meta_rsv_lock);
}