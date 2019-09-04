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
struct nfs_server {TYPE_4__* nfs_client; } ;
struct TYPE_7__ {int /*<<< orphan*/  clientid; } ;
struct TYPE_5__ {TYPE_3__ lock_owner; int /*<<< orphan*/  seq_args; } ;
struct TYPE_6__ {int /*<<< orphan*/  seq_res; } ;
struct nfs_release_lockowner_data {int /*<<< orphan*/  timestamp; TYPE_1__ args; TYPE_2__ res; struct nfs_server* server; } ;
struct TYPE_8__ {int /*<<< orphan*/  cl_clientid; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  nfs4_setup_sequence (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rpc_task*) ; 

__attribute__((used)) static void nfs4_release_lockowner_prepare(struct rpc_task *task, void *calldata)
{
	struct nfs_release_lockowner_data *data = calldata;
	struct nfs_server *server = data->server;
	nfs4_setup_sequence(server->nfs_client, &data->args.seq_args,
			   &data->res.seq_res, task);
	data->args.lock_owner.clientid = server->nfs_client->cl_clientid;
	data->timestamp = jiffies;
}