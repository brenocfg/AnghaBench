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
typedef  void* u32 ;
struct nfs4_slot_table {int dummy; } ;
struct nfs4_slot {void* seq_nr_last_acked; void* seq_nr_highest_sent; void* seq_nr; void* slot_nr; struct nfs4_slot_table* table; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct nfs4_slot* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs4_slot *nfs4_new_slot(struct nfs4_slot_table  *tbl,
		u32 slotid, u32 seq_init, gfp_t gfp_mask)
{
	struct nfs4_slot *slot;

	slot = kzalloc(sizeof(*slot), gfp_mask);
	if (slot) {
		slot->table = tbl;
		slot->slot_nr = slotid;
		slot->seq_nr = seq_init;
		slot->seq_nr_highest_sent = seq_init;
		slot->seq_nr_last_acked = seq_init - 1;
	}
	return slot;
}