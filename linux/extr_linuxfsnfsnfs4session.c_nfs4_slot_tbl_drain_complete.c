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
struct nfs4_slot_table {int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs4_slot_tbl_draining (struct nfs4_slot_table*) ; 

void nfs4_slot_tbl_drain_complete(struct nfs4_slot_table *tbl)
{
	if (nfs4_slot_tbl_draining(tbl))
		complete(&tbl->complete);
}