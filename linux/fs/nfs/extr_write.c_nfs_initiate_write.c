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
struct rpc_task_setup {int priority; int /*<<< orphan*/  rpc_client; } ;
struct rpc_message {int dummy; } ;
struct nfs_rpc_ops {int /*<<< orphan*/  (* write_setup ) (struct nfs_pgio_header*,struct rpc_message*,int /*<<< orphan*/ *) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  stable; } ;
struct nfs_pgio_header {TYPE_1__ args; int /*<<< orphan*/  good_bytes; int /*<<< orphan*/  io_start; int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int flush_task_priority (int) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pgio_header*,struct rpc_message*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfs_initiate_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_initiate_write(struct nfs_pgio_header *hdr,
			       struct rpc_message *msg,
			       const struct nfs_rpc_ops *rpc_ops,
			       struct rpc_task_setup *task_setup_data, int how)
{
	int priority = flush_task_priority(how);

	task_setup_data->priority = priority;
	rpc_ops->write_setup(hdr, msg, &task_setup_data->rpc_client);
	trace_nfs_initiate_write(hdr->inode, hdr->io_start, hdr->good_bytes,
				 hdr->args.stable);
}