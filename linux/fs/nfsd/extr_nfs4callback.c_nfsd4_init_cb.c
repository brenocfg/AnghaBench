#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfsd4_callback_ops {int dummy; } ;
struct TYPE_2__ {struct nfsd4_callback* rpc_resp; struct nfsd4_callback* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfsd4_callback {int cb_seq_status; int cb_need_restart; int cb_holds_slot; scalar_t__ cb_status; int /*<<< orphan*/  cb_work; struct nfsd4_callback_ops const* cb_ops; TYPE_1__ cb_msg; struct nfs4_client* cb_clp; } ;
struct nfs4_client {int dummy; } ;
typedef  enum nfsd4_cb_op { ____Placeholder_nfsd4_cb_op } nfsd4_cb_op ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_cb_procedures ; 
 int /*<<< orphan*/  nfsd4_run_cb_work ; 

void nfsd4_init_cb(struct nfsd4_callback *cb, struct nfs4_client *clp,
		const struct nfsd4_callback_ops *ops, enum nfsd4_cb_op op)
{
	cb->cb_clp = clp;
	cb->cb_msg.rpc_proc = &nfs4_cb_procedures[op];
	cb->cb_msg.rpc_argp = cb;
	cb->cb_msg.rpc_resp = cb;
	cb->cb_ops = ops;
	INIT_WORK(&cb->cb_work, nfsd4_run_cb_work);
	cb->cb_seq_status = 1;
	cb->cb_status = 0;
	cb->cb_need_restart = false;
	cb->cb_holds_slot = false;
}