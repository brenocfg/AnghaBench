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
struct nfs4_slot_table {int /*<<< orphan*/  slot_tbl_lock; int /*<<< orphan*/  slot_tbl_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_SLOT_TBL_DRAINING ; 
 int /*<<< orphan*/  nfs41_wake_slot_table (struct nfs4_slot_table*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_end_drain_slot_table(struct nfs4_slot_table *tbl)
{
	if (test_and_clear_bit(NFS4_SLOT_TBL_DRAINING, &tbl->slot_tbl_state)) {
		spin_lock(&tbl->slot_tbl_lock);
		nfs41_wake_slot_table(tbl);
		spin_unlock(&tbl->slot_tbl_lock);
	}
}