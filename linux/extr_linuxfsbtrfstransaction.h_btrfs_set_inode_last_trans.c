#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct btrfs_trans_handle {TYPE_1__* transaction; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__* root; int /*<<< orphan*/  last_log_commit; int /*<<< orphan*/  last_sub_trans; int /*<<< orphan*/  last_trans; } ;
struct TYPE_5__ {int /*<<< orphan*/  last_log_commit; int /*<<< orphan*/  log_transid; } ;
struct TYPE_4__ {int /*<<< orphan*/  transid; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void btrfs_set_inode_last_trans(struct btrfs_trans_handle *trans,
					      struct inode *inode)
{
	spin_lock(&BTRFS_I(inode)->lock);
	BTRFS_I(inode)->last_trans = trans->transaction->transid;
	BTRFS_I(inode)->last_sub_trans = BTRFS_I(inode)->root->log_transid;
	BTRFS_I(inode)->last_log_commit = BTRFS_I(inode)->root->last_log_commit;
	spin_unlock(&BTRFS_I(inode)->lock);
}