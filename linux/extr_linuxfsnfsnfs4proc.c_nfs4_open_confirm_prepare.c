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
struct TYPE_8__ {int /*<<< orphan*/  seq_res; } ;
struct TYPE_7__ {int /*<<< orphan*/  seq_args; } ;
struct TYPE_6__ {TYPE_1__* server; } ;
struct nfs4_opendata {TYPE_4__ c_res; TYPE_3__ c_arg; TYPE_2__ o_arg; } ;
struct TYPE_5__ {int /*<<< orphan*/  nfs_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_setup_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rpc_task*) ; 

__attribute__((used)) static void nfs4_open_confirm_prepare(struct rpc_task *task, void *calldata)
{
	struct nfs4_opendata *data = calldata;

	nfs4_setup_sequence(data->o_arg.server->nfs_client,
			   &data->c_arg.seq_args, &data->c_res.seq_res, task);
}