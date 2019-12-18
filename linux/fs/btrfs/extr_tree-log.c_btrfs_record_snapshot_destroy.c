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
struct btrfs_trans_handle {int /*<<< orphan*/  transid; } ;
struct btrfs_inode {int /*<<< orphan*/  log_mutex; int /*<<< orphan*/  last_unlink_trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void btrfs_record_snapshot_destroy(struct btrfs_trans_handle *trans,
				   struct btrfs_inode *dir)
{
	mutex_lock(&dir->log_mutex);
	dir->last_unlink_trans = trans->transid;
	mutex_unlock(&dir->log_mutex);
}