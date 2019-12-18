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
struct rpc_task {int /*<<< orphan*/  tk_status; } ;
struct TYPE_5__ {int /*<<< orphan*/  eof; int /*<<< orphan*/  count; } ;
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
struct nfs_pgio_header {TYPE_1__ res; TYPE_2__ args; } ;
struct inode {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int (* read_done ) (struct rpc_task*,struct nfs_pgio_header*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ESTALE ; 
 int /*<<< orphan*/  NFSIOS_SERVERREADBYTES ; 
 TYPE_4__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_STALE ; 
 TYPE_3__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  nfs_add_stats (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_mark_for_revalidate (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct rpc_task*,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  trace_nfs_readpage_done (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_readpage_done(struct rpc_task *task,
			     struct nfs_pgio_header *hdr,
			     struct inode *inode)
{
	int status = NFS_PROTO(inode)->read_done(task, hdr);
	if (status != 0)
		return status;

	nfs_add_stats(inode, NFSIOS_SERVERREADBYTES, hdr->res.count);
	trace_nfs_readpage_done(inode, task->tk_status,
				hdr->args.offset, hdr->res.eof);

	if (task->tk_status == -ESTALE) {
		set_bit(NFS_INO_STALE, &NFS_I(inode)->flags);
		nfs_mark_for_revalidate(inode);
	}
	return 0;
}