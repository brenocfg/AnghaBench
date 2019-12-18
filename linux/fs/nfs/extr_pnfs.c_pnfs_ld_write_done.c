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
struct TYPE_3__ {scalar_t__ count; } ;
struct nfs_pgio_header {TYPE_2__* mds_ops; int /*<<< orphan*/  pnfs_error; int /*<<< orphan*/  task; TYPE_1__ res; scalar_t__ mds_offset; int /*<<< orphan*/  lseg; int /*<<< orphan*/  inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* rpc_release ) (struct nfs_pgio_header*) ;int /*<<< orphan*/  (* rpc_call_done ) (int /*<<< orphan*/ *,struct nfs_pgio_header*) ;} ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pnfs_ld_handle_write_error (struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  pnfs_set_layoutcommit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  stub2 (struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  trace_nfs4_pnfs_write (struct nfs_pgio_header*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void pnfs_ld_write_done(struct nfs_pgio_header *hdr)
{
	if (likely(!hdr->pnfs_error)) {
		pnfs_set_layoutcommit(hdr->inode, hdr->lseg,
				hdr->mds_offset + hdr->res.count);
		hdr->mds_ops->rpc_call_done(&hdr->task, hdr);
	}
	trace_nfs4_pnfs_write(hdr, hdr->pnfs_error);
	if (unlikely(hdr->pnfs_error))
		pnfs_ld_handle_write_error(hdr);
	hdr->mds_ops->rpc_release(hdr);
}