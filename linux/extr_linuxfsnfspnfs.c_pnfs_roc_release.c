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
struct pnfs_layout_hdr {int dummy; } ;
struct nfs4_xdr_opaque_data {TYPE_1__* ops; } ;
struct nfs4_layoutreturn_res {int /*<<< orphan*/  stateid; scalar_t__ lrs_present; } ;
struct nfs4_layoutreturn_args {int /*<<< orphan*/  inode; int /*<<< orphan*/  range; int /*<<< orphan*/  stateid; struct nfs4_xdr_opaque_data* ld_private; struct pnfs_layout_hdr* layout; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (struct nfs4_xdr_opaque_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pnfs_layoutreturn_free_lsegs (struct pnfs_layout_hdr*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pnfs_put_layout_hdr (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  stub1 (struct nfs4_xdr_opaque_data*) ; 
 int /*<<< orphan*/  trace_nfs4_layoutreturn_on_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pnfs_roc_release(struct nfs4_layoutreturn_args *args,
		struct nfs4_layoutreturn_res *res,
		int ret)
{
	struct pnfs_layout_hdr *lo = args->layout;
	const nfs4_stateid *arg_stateid = NULL;
	const nfs4_stateid *res_stateid = NULL;
	struct nfs4_xdr_opaque_data *ld_private = args->ld_private;

	if (ret == 0) {
		arg_stateid = &args->stateid;
		if (res->lrs_present)
			res_stateid = &res->stateid;
	}
	pnfs_layoutreturn_free_lsegs(lo, arg_stateid, &args->range,
			res_stateid);
	if (ld_private && ld_private->ops && ld_private->ops->free)
		ld_private->ops->free(ld_private);
	pnfs_put_layout_hdr(lo);
	trace_nfs4_layoutreturn_on_close(args->inode, 0);
}