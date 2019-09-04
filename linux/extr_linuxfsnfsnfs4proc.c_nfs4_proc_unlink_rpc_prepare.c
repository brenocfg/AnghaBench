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
struct TYPE_7__ {int /*<<< orphan*/  seq_res; } ;
struct TYPE_6__ {int /*<<< orphan*/  seq_args; } ;
struct nfs_unlinkdata {TYPE_3__ res; TYPE_2__ args; TYPE_1__* dentry; } ;
struct TYPE_8__ {int /*<<< orphan*/  nfs_client; } ;
struct TYPE_5__ {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 TYPE_4__* NFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_setup_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rpc_task*) ; 

__attribute__((used)) static void nfs4_proc_unlink_rpc_prepare(struct rpc_task *task, struct nfs_unlinkdata *data)
{
	nfs4_setup_sequence(NFS_SB(data->dentry->d_sb)->nfs_client,
			&data->args.seq_args,
			&data->res.seq_res,
			task);
}