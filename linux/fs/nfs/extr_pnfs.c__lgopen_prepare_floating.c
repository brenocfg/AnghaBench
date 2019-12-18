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
struct pnfs_layout_range {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  iomode; } ;
struct nfs_open_context {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * lg_res; } ;
struct TYPE_4__ {int fmode; int /*<<< orphan*/ * lg_args; } ;
struct nfs4_opendata {TYPE_1__ o_res; TYPE_2__ o_arg; struct nfs4_layoutget* lgp; } ;
struct nfs4_layoutget {int /*<<< orphan*/  res; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IOMODE_READ ; 
 int /*<<< orphan*/  IOMODE_RW ; 
 int /*<<< orphan*/  NFS4_MAX_UINT64 ; 
 int /*<<< orphan*/  current_stateid ; 
 struct nfs4_layoutget* pnfs_alloc_init_layoutget_args (int /*<<< orphan*/ *,struct nfs_open_context*,int /*<<< orphan*/ *,struct pnfs_layout_range*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _lgopen_prepare_floating(struct nfs4_opendata *data,
				     struct nfs_open_context *ctx)
{
	struct pnfs_layout_range rng = {
		.iomode = (data->o_arg.fmode & FMODE_WRITE) ?
			  IOMODE_RW: IOMODE_READ,
		.offset = 0,
		.length = NFS4_MAX_UINT64,
	};
	struct nfs4_layoutget *lgp;

	lgp = pnfs_alloc_init_layoutget_args(NULL, ctx, &current_stateid,
					     &rng, GFP_KERNEL);
	if (!lgp)
		return;
	data->lgp = lgp;
	data->o_arg.lg_args = &lgp->args;
	data->o_res.lg_res = &lgp->res;
}