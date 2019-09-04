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
struct nfs4_slot_table {int dummy; } ;
struct nfs4_slot {int /*<<< orphan*/  slot_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_lock_slot (struct nfs4_slot_table*,struct nfs4_slot*) ; 
 scalar_t__ nfs4_test_locked_slot (struct nfs4_slot_table*,int /*<<< orphan*/ ) ; 

bool nfs4_try_to_lock_slot(struct nfs4_slot_table *tbl, struct nfs4_slot *slot)
{
	if (nfs4_test_locked_slot(tbl, slot->slot_nr))
		return false;
	nfs4_lock_slot(tbl, slot);
	return true;
}