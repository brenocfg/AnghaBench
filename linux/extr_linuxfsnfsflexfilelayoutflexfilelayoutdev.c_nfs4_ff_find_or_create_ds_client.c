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
typedef  int /*<<< orphan*/  u32 ;
struct rpc_clnt {int dummy; } ;
struct pnfs_layout_segment {int dummy; } ;
struct nfs_client {struct rpc_clnt* cl_rpcclient; } ;
struct nfs4_ff_layout_mirror {TYPE_2__* mirror_ds; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ds_versions; } ;
struct TYPE_3__ {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct nfs4_ff_layout_mirror* FF_LAYOUT_COMP (struct pnfs_layout_segment*,int /*<<< orphan*/ ) ; 
 struct rpc_clnt* nfs4_find_or_create_ds_client (struct nfs_client*,struct inode*) ; 

struct rpc_clnt *
nfs4_ff_find_or_create_ds_client(struct pnfs_layout_segment *lseg, u32 ds_idx,
				 struct nfs_client *ds_clp, struct inode *inode)
{
	struct nfs4_ff_layout_mirror *mirror = FF_LAYOUT_COMP(lseg, ds_idx);

	switch (mirror->mirror_ds->ds_versions[0].version) {
	case 3:
		/* For NFSv3 DS, flavor is set when creating DS connections */
		return ds_clp->cl_rpcclient;
	case 4:
		return nfs4_find_or_create_ds_client(ds_clp, inode);
	default:
		BUG();
	}
}