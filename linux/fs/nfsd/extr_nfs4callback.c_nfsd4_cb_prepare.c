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
struct rpc_task {int dummy; } ;
struct nfsd4_callback {int cb_seq_status; int cb_holds_slot; scalar_t__ cb_status; struct nfs4_client* cb_clp; } ;
struct nfs4_client {scalar_t__ cl_minorversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd41_cb_get_slot (struct nfs4_client*,struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_call_start (struct rpc_task*) ; 

__attribute__((used)) static void nfsd4_cb_prepare(struct rpc_task *task, void *calldata)
{
	struct nfsd4_callback *cb = calldata;
	struct nfs4_client *clp = cb->cb_clp;
	u32 minorversion = clp->cl_minorversion;

	/*
	 * cb_seq_status is only set in decode_cb_sequence4res,
	 * and so will remain 1 if an rpc level failure occurs.
	 */
	cb->cb_seq_status = 1;
	cb->cb_status = 0;
	if (minorversion) {
		if (!cb->cb_holds_slot && !nfsd41_cb_get_slot(clp, task))
			return;
		cb->cb_holds_slot = true;
	}
	rpc_call_start(task);
}