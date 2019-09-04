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
struct nfs4_slot_table {scalar_t__ max_slotid; } ;
struct nfs4_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
 struct nfs4_slot* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 struct nfs4_slot* nfs4_find_or_create_slot (struct nfs4_slot_table*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct nfs4_slot *nfs4_lookup_slot(struct nfs4_slot_table *tbl, u32 slotid)
{
	if (slotid <= tbl->max_slotid)
		return nfs4_find_or_create_slot(tbl, slotid, 0, GFP_NOWAIT);
	return ERR_PTR(-E2BIG);
}