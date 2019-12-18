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
struct nfs_pageio_descriptor {int /*<<< orphan*/ * pg_lseg; int /*<<< orphan*/  pg_inode; int /*<<< orphan*/  pg_error; } ;
struct nfs_page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  layout; } ;

/* Variables and functions */
 unsigned int FF_LAYOUT_MIRROR_COUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IOMODE_RW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS4_MAX_UINT64 ; 
 TYPE_1__* NFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_pageio_reset_write_mds (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_req_openctx (struct nfs_page*) ; 
 int /*<<< orphan*/ * pnfs_update_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_pnfs_mds_fallback_pg_get_mirror_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
ff_layout_pg_get_mirror_count_write(struct nfs_pageio_descriptor *pgio,
				    struct nfs_page *req)
{
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
			goto out;
		}
	}
	if (pgio->pg_lseg)
		return FF_LAYOUT_MIRROR_COUNT(pgio->pg_lseg);

	trace_pnfs_mds_fallback_pg_get_mirror_count(pgio->pg_inode,
			0, NFS4_MAX_UINT64, IOMODE_RW,
			NFS_I(pgio->pg_inode)->layout,
			pgio->pg_lseg);
	/* no lseg means that pnfs is not in use, so no mirroring here */
	nfs_pageio_reset_write_mds(pgio);
out:
	return 1;
}