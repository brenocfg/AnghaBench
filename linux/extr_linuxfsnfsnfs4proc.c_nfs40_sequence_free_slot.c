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
struct nfs4_slot_table {int /*<<< orphan*/  slot_tbl_lock; } ;
struct nfs4_slot {struct nfs4_slot_table* table; } ;
struct nfs4_sequence_res {struct nfs4_slot* sr_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs41_wake_and_assign_slot (struct nfs4_slot_table*,struct nfs4_slot*) ; 
 int /*<<< orphan*/  nfs4_free_slot (struct nfs4_slot_table*,struct nfs4_slot*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs40_sequence_free_slot(struct nfs4_sequence_res *res)
{
	struct nfs4_slot *slot = res->sr_slot;
	struct nfs4_slot_table *tbl;

	tbl = slot->table;
	spin_lock(&tbl->slot_tbl_lock);
	if (!nfs41_wake_and_assign_slot(tbl, slot))
		nfs4_free_slot(tbl, slot);
	spin_unlock(&tbl->slot_tbl_lock);

	res->sr_slot = NULL;
}