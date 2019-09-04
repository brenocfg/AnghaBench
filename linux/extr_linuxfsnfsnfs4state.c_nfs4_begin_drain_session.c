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
 int nfs4_drain_slot_tbl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_begin_drain_session(struct nfs_client *clp)
{
	struct nfs4_session *ses = clp->cl_session;
	int ret;

	if (clp->cl_slot_tbl)
		return nfs4_drain_slot_tbl(clp->cl_slot_tbl);

	/* back channel */
	ret = nfs4_drain_slot_tbl(&ses->bc_slot_table);
	if (ret)
		return ret;
	/* fore channel */
	return nfs4_drain_slot_tbl(&ses->fc_slot_table);
}