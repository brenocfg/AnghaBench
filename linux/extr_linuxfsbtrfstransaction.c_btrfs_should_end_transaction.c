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
struct TYPE_2__ {scalar_t__ flushing; } ;
struct btrfs_transaction {scalar_t__ state; TYPE_1__ delayed_refs; } ;
struct btrfs_trans_handle {int delayed_ref_updates; struct btrfs_transaction* transaction; } ;

/* Variables and functions */
 scalar_t__ TRANS_STATE_BLOCKED ; 
 int btrfs_run_delayed_refs (struct btrfs_trans_handle*,int) ; 
 int should_end_transaction (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  smp_mb () ; 

int btrfs_should_end_transaction(struct btrfs_trans_handle *trans)
{
	struct btrfs_transaction *cur_trans = trans->transaction;
	int updates;
	int err;

	smp_mb();
	if (cur_trans->state >= TRANS_STATE_BLOCKED ||
	    cur_trans->delayed_refs.flushing)
		return 1;

	updates = trans->delayed_ref_updates;
	trans->delayed_ref_updates = 0;
	if (updates) {
		err = btrfs_run_delayed_refs(trans, updates * 2);
		if (err) /* Error code will also eval true */
			return err;
	}

	return should_end_transaction(trans);
}