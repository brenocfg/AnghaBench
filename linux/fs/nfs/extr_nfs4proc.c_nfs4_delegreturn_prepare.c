#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {int dummy; } ;
struct pnfs_layout_hdr {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  seq_res; TYPE_3__* server; int /*<<< orphan*/ * lr_res; } ;
struct TYPE_9__ {int /*<<< orphan*/  seq_args; TYPE_2__* lr_args; } ;
struct TYPE_6__ {int /*<<< orphan*/  roc; } ;
struct nfs4_delegreturndata {TYPE_5__ res; TYPE_4__ args; int /*<<< orphan*/  inode; TYPE_1__ lr; } ;
struct TYPE_8__ {int /*<<< orphan*/  nfs_client; } ;
struct TYPE_7__ {struct pnfs_layout_hdr* layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_setup_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rpc_task*) ; 
 scalar_t__ nfs4_wait_on_layoutreturn (int /*<<< orphan*/ ,struct rpc_task*) ; 
 int /*<<< orphan*/  pnfs_layout_is_valid (struct pnfs_layout_hdr*) ; 

__attribute__((used)) static void nfs4_delegreturn_prepare(struct rpc_task *task, void *data)
{
	struct nfs4_delegreturndata *d_data;
	struct pnfs_layout_hdr *lo;

	d_data = (struct nfs4_delegreturndata *)data;

	if (!d_data->lr.roc && nfs4_wait_on_layoutreturn(d_data->inode, task))
		return;

	lo = d_data->args.lr_args ? d_data->args.lr_args->layout : NULL;
	if (lo && !pnfs_layout_is_valid(lo)) {
		d_data->args.lr_args = NULL;
		d_data->res.lr_res = NULL;
	}

	nfs4_setup_sequence(d_data->res.server->nfs_client,
			&d_data->args.seq_args,
			&d_data->res.seq_res,
			task);
}