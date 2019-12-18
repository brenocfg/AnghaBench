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
struct nfs4_slot_table {int /*<<< orphan*/  max_slots; struct nfs4_slot* slots; } ;
struct nfs4_slot {scalar_t__ slot_nr; struct nfs4_slot* next; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct nfs4_slot* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct nfs4_slot* nfs4_new_slot (struct nfs4_slot_table*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs4_slot *nfs4_find_or_create_slot(struct nfs4_slot_table  *tbl,
		u32 slotid, u32 seq_init, gfp_t gfp_mask)
{
	struct nfs4_slot **p, *slot;

	p = &tbl->slots;
	for (;;) {
		if (*p == NULL) {
			*p = nfs4_new_slot(tbl, tbl->max_slots,
					seq_init, gfp_mask);
			if (*p == NULL)
				break;
			tbl->max_slots++;
		}
		slot = *p;
		if (slot->slot_nr == slotid)
			return slot;
		p = &slot->next;
	}
	return ERR_PTR(-ENOMEM);
}