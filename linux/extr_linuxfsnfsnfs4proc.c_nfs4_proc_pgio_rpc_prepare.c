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
struct TYPE_5__ {TYPE_3__* context; int /*<<< orphan*/  lock_context; int /*<<< orphan*/  stateid; int /*<<< orphan*/  seq_args; } ;
struct TYPE_6__ {int /*<<< orphan*/  seq_res; } ;
struct nfs_pgio_header {TYPE_1__ args; int /*<<< orphan*/  rw_mode; TYPE_2__ res; int /*<<< orphan*/  inode; } ;
struct TYPE_8__ {int /*<<< orphan*/  nfs_client; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NFS_CONTEXT_BAD ; 
 TYPE_4__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int nfs4_set_rw_stateid (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs4_setup_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rpc_task*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs4_proc_pgio_rpc_prepare(struct rpc_task *task,
				      struct nfs_pgio_header *hdr)
{
	if (nfs4_setup_sequence(NFS_SERVER(hdr->inode)->nfs_client,
			&hdr->args.seq_args,
			&hdr->res.seq_res,
			task))
		return 0;
	if (nfs4_set_rw_stateid(&hdr->args.stateid, hdr->args.context,
				hdr->args.lock_context,
				hdr->rw_mode) == -EIO)
		return -EIO;
	if (unlikely(test_bit(NFS_CONTEXT_BAD, &hdr->args.context->flags)))
		return -EIO;
	return 0;
}