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
struct nfs_pgio_mirror {int /*<<< orphan*/  pg_bsize; } ;
struct nfs_pageio_descriptor {int pg_mirror_count; scalar_t__ pg_maxretrans; int /*<<< orphan*/ * pg_lseg; int /*<<< orphan*/  pg_inode; struct nfs_pgio_mirror* pg_mirrors; int /*<<< orphan*/  pg_dreq; int /*<<< orphan*/  pg_error; } ;
struct nfs_page {int dummy; } ;
struct nfs_commit_info {int dummy; } ;
struct nfs4_pnfs_ds {int dummy; } ;
struct nfs4_ff_layout_mirror {TYPE_2__* mirror_ds; } ;
struct TYPE_8__ {int /*<<< orphan*/  layout; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {TYPE_1__* ds_versions; } ;
struct TYPE_5__ {int /*<<< orphan*/  wsize; } ;

/* Variables and functions */
 struct nfs4_ff_layout_mirror* FF_LAYOUT_COMP (int /*<<< orphan*/ *,int) ; 
 int FF_LAYOUT_MIRROR_COUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IOMODE_RW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS4_MAX_UINT64 ; 
 TYPE_4__* NFS_I (int /*<<< orphan*/ ) ; 
 int NFS_MOUNT_SOFT ; 
 int NFS_MOUNT_SOFTERR ; 
 TYPE_3__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int ff_layout_alloc_commit_info (int /*<<< orphan*/ *,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_layout_no_fallback_to_mds (int /*<<< orphan*/ *) ; 
 scalar_t__ io_maxretrans ; 
 struct nfs4_pnfs_ds* nfs4_ff_layout_prepare_ds (int /*<<< orphan*/ *,struct nfs4_ff_layout_mirror*,int) ; 
 int /*<<< orphan*/  nfs_init_cinfo (struct nfs_commit_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pageio_reset_write_mds (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_req_openctx (struct nfs_page*) ; 
 int /*<<< orphan*/  pnfs_generic_pg_check_layout (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  pnfs_put_lseg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pnfs_update_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 int /*<<< orphan*/  trace_pnfs_mds_fallback_pg_init_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ff_layout_pg_init_write(struct nfs_pageio_descriptor *pgio,
			struct nfs_page *req)
{
	struct nfs4_ff_layout_mirror *mirror;
	struct nfs_pgio_mirror *pgm;
	struct nfs_commit_info cinfo;
	struct nfs4_pnfs_ds *ds;
	int i;
	int status;

retry:
	pnfs_generic_pg_check_layout(pgio);
	if (!pgio->pg_lseg) {
		pgio->pg_lseg = pnfs_update_layout(pgio->pg_inode,
						   nfs_req_openctx(req),
						   0,
						   NFS4_MAX_UINT64,
						   IOMODE_RW,
						   false,
						   GFP_NOFS);
		if (IS_ERR(pgio->pg_lseg)) {
			pgio->pg_error = PTR_ERR(pgio->pg_lseg);
			pgio->pg_lseg = NULL;
			return;
		}
	}
	/* If no lseg, fall back to write through mds */
	if (pgio->pg_lseg == NULL)
		goto out_mds;

	nfs_init_cinfo(&cinfo, pgio->pg_inode, pgio->pg_dreq);
	status = ff_layout_alloc_commit_info(pgio->pg_lseg, &cinfo, GFP_NOFS);
	if (status < 0)
		goto out_mds;

	/* Use a direct mapping of ds_idx to pgio mirror_idx */
	if (WARN_ON_ONCE(pgio->pg_mirror_count !=
	    FF_LAYOUT_MIRROR_COUNT(pgio->pg_lseg)))
		goto out_mds;

	for (i = 0; i < pgio->pg_mirror_count; i++) {
		mirror = FF_LAYOUT_COMP(pgio->pg_lseg, i);
		ds = nfs4_ff_layout_prepare_ds(pgio->pg_lseg, mirror, true);
		if (!ds) {
			if (!ff_layout_no_fallback_to_mds(pgio->pg_lseg))
				goto out_mds;
			pnfs_put_lseg(pgio->pg_lseg);
			pgio->pg_lseg = NULL;
			/* Sleep for 1 second before retrying */
			ssleep(1);
			goto retry;
		}
		pgm = &pgio->pg_mirrors[i];
		pgm->pg_bsize = mirror->mirror_ds->ds_versions[0].wsize;
	}

	if (NFS_SERVER(pgio->pg_inode)->flags &
			(NFS_MOUNT_SOFT|NFS_MOUNT_SOFTERR))
		pgio->pg_maxretrans = io_maxretrans;
	return;

out_mds:
	trace_pnfs_mds_fallback_pg_init_write(pgio->pg_inode,
			0, NFS4_MAX_UINT64, IOMODE_RW,
			NFS_I(pgio->pg_inode)->layout,
			pgio->pg_lseg);
	pnfs_put_lseg(pgio->pg_lseg);
	pgio->pg_lseg = NULL;
	pgio->pg_maxretrans = 0;
	nfs_pageio_reset_write_mds(pgio);
}