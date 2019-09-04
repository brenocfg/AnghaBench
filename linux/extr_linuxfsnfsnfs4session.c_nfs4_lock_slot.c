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
typedef  scalar_t__ u32 ;
struct nfs4_slot_table {scalar_t__ highest_used_slotid; int /*<<< orphan*/  generation; int /*<<< orphan*/  used_slots; } ;
struct nfs4_slot {scalar_t__ slot_nr; int /*<<< orphan*/  generation; } ;

/* Variables and functions */
 scalar_t__ NFS4_NO_SLOT ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_lock_slot(struct nfs4_slot_table *tbl,
		struct nfs4_slot *slot)
{
	u32 slotid = slot->slot_nr;

	__set_bit(slotid, tbl->used_slots);
	if (slotid > tbl->highest_used_slotid ||
	    tbl->highest_used_slotid == NFS4_NO_SLOT)
		tbl->highest_used_slotid = slotid;
	slot->generation = tbl->generation;
}