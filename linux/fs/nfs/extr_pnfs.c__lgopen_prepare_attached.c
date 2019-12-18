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
struct pnfs_layout_range {scalar_t__ iomode; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct pnfs_layout_hdr {int dummy; } ;
struct nfs_open_context {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lg_res; } ;
struct TYPE_7__ {int fmode; int /*<<< orphan*/ * lg_args; } ;
struct nfs4_opendata {TYPE_4__ o_res; TYPE_3__ o_arg; struct nfs4_layoutget* lgp; TYPE_1__* dentry; } ;
struct nfs4_layoutget {int /*<<< orphan*/  res; int /*<<< orphan*/  args; } ;
struct inode {TYPE_2__* i_mapping; } ;
struct TYPE_6__ {scalar_t__ nrpages; } ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IOMODE_READ ; 
 scalar_t__ IOMODE_RW ; 
 int /*<<< orphan*/  NFS4_MAX_UINT64 ; 
 struct pnfs_layout_hdr* _pnfs_grab_empty_layout (struct inode*,struct nfs_open_context*) ; 
 int /*<<< orphan*/  current_stateid ; 
 scalar_t__ i_size_read (struct inode*) ; 
 struct nfs4_layoutget* pnfs_alloc_init_layoutget_args (struct inode*,struct nfs_open_context*,int /*<<< orphan*/ *,struct pnfs_layout_range*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_clear_first_layoutget (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  pnfs_put_layout_hdr (struct pnfs_layout_hdr*) ; 

__attribute__((used)) static void _lgopen_prepare_attached(struct nfs4_opendata *data,
				     struct nfs_open_context *ctx)
{
	struct inode *ino = data->dentry->d_inode;
	struct pnfs_layout_range rng = {
		.iomode = (data->o_arg.fmode & FMODE_WRITE) ?
			  IOMODE_RW: IOMODE_READ,
		.offset = 0,
		.length = NFS4_MAX_UINT64,
	};
	struct nfs4_layoutget *lgp;
	struct pnfs_layout_hdr *lo;

	/* Heuristic: don't send layoutget if we have cached data */
	if (rng.iomode == IOMODE_READ &&
	   (i_size_read(ino) == 0 || ino->i_mapping->nrpages != 0))
		return;

	lo = _pnfs_grab_empty_layout(ino, ctx);
	if (!lo)
		return;
	lgp = pnfs_alloc_init_layoutget_args(ino, ctx, &current_stateid,
					     &rng, GFP_KERNEL);
	if (!lgp) {
		pnfs_clear_first_layoutget(lo);
		pnfs_put_layout_hdr(lo);
		return;
	}
	data->lgp = lgp;
	data->o_arg.lg_args = &lgp->args;
	data->o_res.lg_res = &lgp->res;
}