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
struct nfs_pgio_header {int /*<<< orphan*/  inode; } ;
struct TYPE_2__ {int (* pgio_rpc_prepare ) (struct rpc_task*,struct nfs_pgio_header*) ;} ;

/* Variables and functions */
 TYPE_1__* NFS_PROTO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_exit (struct rpc_task*,int) ; 
 int stub1 (struct rpc_task*,struct nfs_pgio_header*) ; 

__attribute__((used)) static void nfs_pgio_prepare(struct rpc_task *task, void *calldata)
{
	struct nfs_pgio_header *hdr = calldata;
	int err;
	err = NFS_PROTO(hdr->inode)->pgio_rpc_prepare(task, hdr);
	if (err)
		rpc_exit(task, err);
}