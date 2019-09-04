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
struct nfs_client {int /*<<< orphan*/ * cl_slot_tbl; struct nfs4_session* cl_session; } ;
struct nfs4_session {int /*<<< orphan*/  fc_slot_table; int /*<<< orphan*/  bc_slot_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_end_drain_slot_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_end_drain_session(struct nfs_client *clp)
{
	struct nfs4_session *ses = clp->cl_session;

	if (clp->cl_slot_tbl) {
		nfs4_end_drain_slot_table(clp->cl_slot_tbl);
		return;
	}

	if (ses != NULL) {
		nfs4_end_drain_slot_table(&ses->bc_slot_table);
		nfs4_end_drain_slot_table(&ses->fc_slot_table);
	}
}