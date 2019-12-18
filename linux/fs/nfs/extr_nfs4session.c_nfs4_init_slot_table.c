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
struct nfs4_slot_table {int /*<<< orphan*/  complete; int /*<<< orphan*/  slot_waitq; int /*<<< orphan*/  slot_tbl_waitq; int /*<<< orphan*/  slot_tbl_lock; int /*<<< orphan*/  highest_used_slotid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_NO_SLOT ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_init_priority_wait_queue (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_init_slot_table(struct nfs4_slot_table *tbl, const char *queue)
{
	tbl->highest_used_slotid = NFS4_NO_SLOT;
	spin_lock_init(&tbl->slot_tbl_lock);
	rpc_init_priority_wait_queue(&tbl->slot_tbl_waitq, queue);
	init_waitqueue_head(&tbl->slot_waitq);
	init_completion(&tbl->complete);
}