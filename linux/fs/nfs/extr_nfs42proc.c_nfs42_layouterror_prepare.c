#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {int dummy; } ;
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_stateid; } ;
struct nfs_server {int /*<<< orphan*/  nfs_client; } ;
struct TYPE_8__ {int /*<<< orphan*/  seq_res; } ;
struct TYPE_7__ {unsigned int num_errors; int /*<<< orphan*/  seq_args; TYPE_2__* errors; } ;
struct nfs42_layouterror_data {TYPE_4__ res; TYPE_3__ args; TYPE_1__* lseg; struct inode* inode; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  stateid; } ;
struct TYPE_5__ {struct pnfs_layout_hdr* pls_layout; } ;

/* Variables and functions */
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  nfs4_setup_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rpc_task*) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_layout_is_valid (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  rpc_exit (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfs42_layouterror_prepare(struct rpc_task *task, void *calldata)
{
	struct nfs42_layouterror_data *data = calldata;
	struct inode *inode = data->inode;
	struct nfs_server *server = NFS_SERVER(inode);
	struct pnfs_layout_hdr *lo = data->lseg->pls_layout;
	unsigned i;

	spin_lock(&inode->i_lock);
	if (!pnfs_layout_is_valid(lo)) {
		spin_unlock(&inode->i_lock);
		rpc_exit(task, 0);
		return;
	}
	for (i = 0; i < data->args.num_errors; i++)
		nfs4_stateid_copy(&data->args.errors[i].stateid,
				&lo->plh_stateid);
	spin_unlock(&inode->i_lock);
	nfs4_setup_sequence(server->nfs_client, &data->args.seq_args,
			    &data->res.seq_res, task);
}