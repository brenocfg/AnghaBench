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
struct rpc_task_setup {int flags; } ;
struct rpc_message {int dummy; } ;
struct nfs_rpc_ops {int /*<<< orphan*/  (* read_setup ) (struct nfs_pgio_header*,struct rpc_message*) ;} ;
struct nfs_pgio_header {int /*<<< orphan*/  good_bytes; int /*<<< orphan*/  io_start; struct inode* inode; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_SWAPFILE (struct inode*) ; 
 int NFS_RPC_SWAPFLAGS ; 
 int /*<<< orphan*/  stub1 (struct nfs_pgio_header*,struct rpc_message*) ; 
 int /*<<< orphan*/  trace_nfs_initiate_read (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_initiate_read(struct nfs_pgio_header *hdr,
			      struct rpc_message *msg,
			      const struct nfs_rpc_ops *rpc_ops,
			      struct rpc_task_setup *task_setup_data, int how)
{
	struct inode *inode = hdr->inode;
	int swap_flags = IS_SWAPFILE(inode) ? NFS_RPC_SWAPFLAGS : 0;

	task_setup_data->flags |= swap_flags;
	rpc_ops->read_setup(hdr, msg);
	trace_nfs_initiate_read(inode, hdr->io_start, hdr->good_bytes);
}