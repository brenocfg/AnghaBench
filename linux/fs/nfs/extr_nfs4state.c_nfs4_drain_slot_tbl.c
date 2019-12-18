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
struct nfs4_slot_table {scalar_t__ highest_used_slotid; int /*<<< orphan*/  slot_tbl_lock; int /*<<< orphan*/  complete; int /*<<< orphan*/  slot_tbl_state; } ;

/* Variables and functions */
 scalar_t__ NFS4_NO_SLOT ; 
 int /*<<< orphan*/  NFS4_SLOT_TBL_DRAINING ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_drain_slot_tbl(struct nfs4_slot_table *tbl)
{
	set_bit(NFS4_SLOT_TBL_DRAINING, &tbl->slot_tbl_state);
	spin_lock(&tbl->slot_tbl_lock);
	if (tbl->highest_used_slotid != NFS4_NO_SLOT) {
		reinit_completion(&tbl->complete);
		spin_unlock(&tbl->slot_tbl_lock);
		return wait_for_completion_interruptible(&tbl->complete);
	}
	spin_unlock(&tbl->slot_tbl_lock);
	return 0;
}