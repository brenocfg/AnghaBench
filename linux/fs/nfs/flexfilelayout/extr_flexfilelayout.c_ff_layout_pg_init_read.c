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
struct nfs_pageio_descriptor {int pg_mirror_idx; scalar_t__ pg_error; scalar_t__ pg_maxretrans; int /*<<< orphan*/ * pg_lseg; int /*<<< orphan*/  pg_inode; struct nfs_pgio_mirror* pg_mirrors; } ;
struct nfs_page {int dummy; } ;
struct nfs4_pnfs_ds {int dummy; } ;
struct nfs4_ff_layout_mirror {TYPE_2__* mirror_ds; } ;
struct TYPE_8__ {int /*<<< orphan*/  layout; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {TYPE_1__* ds_versions; } ;
struct TYPE_5__ {int /*<<< orphan*/  rsize; } ;

/* Variables and functions */
 struct nfs4_ff_layout_mirror* FF_LAYOUT_COMP (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IOMODE_READ ; 
 int /*<<< orphan*/  NFS4_MAX_UINT64 ; 
 TYPE_4__* NFS_I (int /*<<< orphan*/ ) ; 
 int NFS_MOUNT_SOFT ; 
 int NFS_MOUNT_SOFTERR ; 
 TYPE_3__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 scalar_t__ ff_layout_avoid_read_on_rw (int /*<<< orphan*/ *) ; 
 struct nfs4_pnfs_ds* ff_layout_choose_best_ds_for_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ff_layout_no_fallback_to_mds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_layout_pg_get_read (struct nfs_pageio_descriptor*,struct nfs_page*,int) ; 
 scalar_t__ io_maxretrans ; 
 int /*<<< orphan*/  nfs_pageio_reset_read_mds (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  pnfs_generic_pg_check_layout (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  pnfs_put_lseg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 int /*<<< orphan*/  trace_pnfs_mds_fallback_pg_init_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ff_layout_pg_init_read(struct nfs_pageio_descriptor *pgio,
			struct nfs_page *req)
{
	struct nfs_pgio_mirror *pgm;
	struct nfs4_ff_layout_mirror *mirror;
	struct nfs4_pnfs_ds *ds;
	int ds_idx;

retry:
	pnfs_generic_pg_check_layout(pgio);
	/* Use full layout for now */
	if (!pgio->pg_lseg) {
		ff_layout_pg_get_read(pgio, req, false);
		if (!pgio->pg_lseg)
			goto out_nolseg;
	}
	if (ff_layout_avoid_read_on_rw(pgio->pg_lseg)) {
		ff_layout_pg_get_read(pgio, req, true);
		if (!pgio->pg_lseg)
			goto out_nolseg;
	}

	ds = ff_layout_choose_best_ds_for_read(pgio->pg_lseg, 0, &ds_idx);
	if (!ds) {
		if (!ff_layout_no_fallback_to_mds(pgio->pg_lseg))
			goto out_mds;
		pnfs_put_lseg(pgio->pg_lseg);
		pgio->pg_lseg = NULL;
		/* Sleep for 1 second before retrying */
		ssleep(1);
		goto retry;
	}

	mirror = FF_LAYOUT_COMP(pgio->pg_lseg, ds_idx);

	pgio->pg_mirror_idx = ds_idx;

	/* read always uses only one mirror - idx 0 for pgio layer */
	pgm = &pgio->pg_mirrors[0];
	pgm->pg_bsize = mirror->mirror_ds->ds_versions[0].rsize;

	if (NFS_SERVER(pgio->pg_inode)->flags &
			(NFS_MOUNT_SOFT|NFS_MOUNT_SOFTERR))
		pgio->pg_maxretrans = io_maxretrans;
	return;
out_nolseg:
	if (pgio->pg_error < 0)
		return;
out_mds:
	trace_pnfs_mds_fallback_pg_init_read(pgio->pg_inode,
			0, NFS4_MAX_UINT64, IOMODE_READ,
			NFS_I(pgio->pg_inode)->layout,
			pgio->pg_lseg);
	pnfs_put_lseg(pgio->pg_lseg);
	pgio->pg_lseg = NULL;
	pgio->pg_maxretrans = 0;
	nfs_pageio_reset_read_mds(pgio);
}