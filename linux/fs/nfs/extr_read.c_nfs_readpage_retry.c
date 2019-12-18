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
struct rpc_task {int /*<<< orphan*/  tk_ops; } ;
struct nfs_pgio_res {scalar_t__ count; } ;
struct nfs_pgio_args {int /*<<< orphan*/  count; int /*<<< orphan*/  pgbase; int /*<<< orphan*/  offset; } ;
struct nfs_pgio_header {int /*<<< orphan*/  mds_offset; int /*<<< orphan*/  pnfs_error; int /*<<< orphan*/  inode; struct nfs_pgio_res res; struct nfs_pgio_args args; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  NFSIOS_SHORTREAD ; 
 int /*<<< orphan*/  nfs_inc_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_set_pgio_error (struct nfs_pgio_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_restart_call_prepare (struct rpc_task*) ; 

__attribute__((used)) static void nfs_readpage_retry(struct rpc_task *task,
			       struct nfs_pgio_header *hdr)
{
	struct nfs_pgio_args *argp = &hdr->args;
	struct nfs_pgio_res  *resp = &hdr->res;

	/* This is a short read! */
	nfs_inc_stats(hdr->inode, NFSIOS_SHORTREAD);
	/* Has the server at least made some progress? */
	if (resp->count == 0) {
		nfs_set_pgio_error(hdr, -EIO, argp->offset);
		return;
	}

	/* For non rpc-based layout drivers, retry-through-MDS */
	if (!task->tk_ops) {
		hdr->pnfs_error = -EAGAIN;
		return;
	}

	/* Yes, so retry the read at the end of the hdr */
	hdr->mds_offset += resp->count;
	argp->offset += resp->count;
	argp->pgbase += resp->count;
	argp->count -= resp->count;
	rpc_restart_call_prepare(task);
}