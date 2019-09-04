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
struct nfs4_call_sync_data {int /*<<< orphan*/  seq_res; int /*<<< orphan*/  seq_args; TYPE_1__* seq_server; } ;
struct TYPE_2__ {int /*<<< orphan*/  nfs_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_setup_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpc_task*) ; 

__attribute__((used)) static void nfs40_call_sync_prepare(struct rpc_task *task, void *calldata)
{
	struct nfs4_call_sync_data *data = calldata;
	nfs4_setup_sequence(data->seq_server->nfs_client,
				data->seq_args, data->seq_res, task);
}