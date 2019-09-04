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
struct nfs4_slot_table {scalar_t__ max_slots; struct nfs4_slot* slots; } ;
struct nfs4_slot {struct nfs4_slot* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfs4_slot*) ; 

__attribute__((used)) static void nfs4_shrink_slot_table(struct nfs4_slot_table  *tbl, u32 newsize)
{
	struct nfs4_slot **p;
	if (newsize >= tbl->max_slots)
		return;

	p = &tbl->slots;
	while (newsize--)
		p = &(*p)->next;
	while (*p) {
		struct nfs4_slot *slot = *p;

		*p = slot->next;
		kfree(slot);
		tbl->max_slots--;
	}
}