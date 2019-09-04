#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  seq_res; } ;
struct TYPE_3__ {int /*<<< orphan*/  seq_args; } ;
struct nfs_commit_data {TYPE_2__ res; TYPE_1__ args; int /*<<< orphan*/  ds_clp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ff_layout_commit_prepare_common (struct rpc_task*,void*) ; 
 scalar_t__ nfs4_setup_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rpc_task*) ; 

__attribute__((used)) static void ff_layout_commit_prepare_v4(struct rpc_task *task, void *data)
{
	struct nfs_commit_data *wdata = data;

	if (nfs4_setup_sequence(wdata->ds_clp,
				&wdata->args.seq_args,
				&wdata->res.seq_res,
				task))
		return;
	ff_layout_commit_prepare_common(task, data);
}