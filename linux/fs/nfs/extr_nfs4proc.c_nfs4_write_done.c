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
struct rpc_task {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq_res; } ;
struct nfs_pgio_header {int (* pgio_done_cb ) (struct rpc_task*,struct nfs_pgio_header*) ;int /*<<< orphan*/  args; TYPE_1__ res; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  nfs4_sequence_done (struct rpc_task*,int /*<<< orphan*/ *) ; 
 int nfs4_write_done_cb (struct rpc_task*,struct nfs_pgio_header*) ; 
 scalar_t__ nfs4_write_stateid_changed (struct rpc_task*,int /*<<< orphan*/ *) ; 
 int stub1 (struct rpc_task*,struct nfs_pgio_header*) ; 

__attribute__((used)) static int nfs4_write_done(struct rpc_task *task, struct nfs_pgio_header *hdr)
{
	if (!nfs4_sequence_done(task, &hdr->res.seq_res))
		return -EAGAIN;
	if (nfs4_write_stateid_changed(task, &hdr->args))
		return -EAGAIN;
	return hdr->pgio_done_cb ? hdr->pgio_done_cb(task, hdr) :
		nfs4_write_done_cb(task, hdr);
}