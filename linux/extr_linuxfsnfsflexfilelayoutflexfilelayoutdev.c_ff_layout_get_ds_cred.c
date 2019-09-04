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
typedef  int /*<<< orphan*/  u32 ;
struct rpc_cred {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  iomode; } ;
struct pnfs_layout_segment {TYPE_1__ pls_range; } ;
struct nfs4_ff_layout_mirror {int dummy; } ;

/* Variables and functions */
 struct nfs4_ff_layout_mirror* FF_LAYOUT_COMP (struct pnfs_layout_segment*,int /*<<< orphan*/ ) ; 
 struct rpc_cred* ff_layout_get_mirror_cred (struct nfs4_ff_layout_mirror*,int /*<<< orphan*/ ) ; 
 struct rpc_cred* get_rpccred (struct rpc_cred*) ; 

struct rpc_cred *
ff_layout_get_ds_cred(struct pnfs_layout_segment *lseg, u32 ds_idx,
		      struct rpc_cred *mdscred)
{
	struct nfs4_ff_layout_mirror *mirror = FF_LAYOUT_COMP(lseg, ds_idx);
	struct rpc_cred *cred;

	if (mirror) {
		cred = ff_layout_get_mirror_cred(mirror, lseg->pls_range.iomode);
		if (!cred)
			cred = get_rpccred(mdscred);
	} else {
		cred = get_rpccred(mdscred);
	}
	return cred;
}