#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct pnfs_layout_segment {TYPE_4__ pls_range; TYPE_5__* pls_layout; } ;
struct nfs_server {int dummy; } ;
struct nfs4_pnfs_ds {TYPE_1__* ds_clp; } ;
struct nfs4_ff_layout_mirror {TYPE_3__* mirror_ds; } ;
struct inode {int dummy; } ;
struct TYPE_11__ {struct inode* plh_inode; } ;
struct TYPE_9__ {TYPE_2__* ds_versions; int /*<<< orphan*/  id_node; struct nfs4_pnfs_ds* ds; } ;
struct TYPE_8__ {unsigned int rsize; unsigned int wsize; int /*<<< orphan*/  minor_version; int /*<<< orphan*/  version; } ;
struct TYPE_7__ {int /*<<< orphan*/  cl_rpcclient; } ;

/* Variables and functions */
 int /*<<< orphan*/  FF_LAYOUT_FROM_HDR (TYPE_5__*) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  NFS4ERR_NXIO ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  OP_ILLEGAL ; 
 int /*<<< orphan*/  dataserver_retrans ; 
 int /*<<< orphan*/  dataserver_timeo ; 
 int /*<<< orphan*/  ff_layout_has_available_ds (struct pnfs_layout_segment*) ; 
 int /*<<< orphan*/  ff_layout_init_mirror_ds (TYPE_5__*,struct nfs4_ff_layout_mirror*) ; 
 int /*<<< orphan*/  ff_layout_send_layouterror (struct pnfs_layout_segment*) ; 
 int /*<<< orphan*/  ff_layout_track_ds_error (int /*<<< orphan*/ ,struct nfs4_ff_layout_mirror*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs4_pnfs_ds_connect (struct nfs_server*,struct nfs4_pnfs_ds*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int nfs_block_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_error_mark_layout_for_return (struct inode*,struct pnfs_layout_segment*) ; 
 int /*<<< orphan*/  rpc_max_payload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 

struct nfs4_pnfs_ds *
nfs4_ff_layout_prepare_ds(struct pnfs_layout_segment *lseg,
			  struct nfs4_ff_layout_mirror *mirror,
			  bool fail_return)
{
	struct nfs4_pnfs_ds *ds = NULL;
	struct inode *ino = lseg->pls_layout->plh_inode;
	struct nfs_server *s = NFS_SERVER(ino);
	unsigned int max_payload;
	int status;

	if (!ff_layout_init_mirror_ds(lseg->pls_layout, mirror))
		goto noconnect;

	ds = mirror->mirror_ds->ds;
	/* matching smp_wmb() in _nfs4_pnfs_v3/4_ds_connect */
	smp_rmb();
	if (ds->ds_clp)
		goto out;

	/* FIXME: For now we assume the server sent only one version of NFS
	 * to use for the DS.
	 */
	status = nfs4_pnfs_ds_connect(s, ds, &mirror->mirror_ds->id_node,
			     dataserver_timeo, dataserver_retrans,
			     mirror->mirror_ds->ds_versions[0].version,
			     mirror->mirror_ds->ds_versions[0].minor_version);

	/* connect success, check rsize/wsize limit */
	if (!status) {
		max_payload =
			nfs_block_size(rpc_max_payload(ds->ds_clp->cl_rpcclient),
				       NULL);
		if (mirror->mirror_ds->ds_versions[0].rsize > max_payload)
			mirror->mirror_ds->ds_versions[0].rsize = max_payload;
		if (mirror->mirror_ds->ds_versions[0].wsize > max_payload)
			mirror->mirror_ds->ds_versions[0].wsize = max_payload;
		goto out;
	}
noconnect:
	ff_layout_track_ds_error(FF_LAYOUT_FROM_HDR(lseg->pls_layout),
				 mirror, lseg->pls_range.offset,
				 lseg->pls_range.length, NFS4ERR_NXIO,
				 OP_ILLEGAL, GFP_NOIO);
	ff_layout_send_layouterror(lseg);
	if (fail_return || !ff_layout_has_available_ds(lseg))
		pnfs_error_mark_layout_for_return(ino, lseg);
	ds = NULL;
out:
	return ds;
}