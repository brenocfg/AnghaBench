#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nfs_pageio_descriptor {int /*<<< orphan*/ * pg_lseg; int /*<<< orphan*/  pg_error; int /*<<< orphan*/  pg_inode; } ;
struct nfs_page {int /*<<< orphan*/  wb_context; } ;

/* Variables and functions */
 unsigned int FF_LAYOUT_MIRROR_COUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IOMODE_RW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS4_MAX_UINT64 ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_pageio_reset_write_mds (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/ * pnfs_update_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
ff_layout_pg_get_mirror_count_write(struct nfs_pageio_descriptor *pgio,
				    struct nfs_page *req)
{
	if (!pgio->pg_lseg) {
		pgio->pg_lseg = pnfs_update_layout(pgio->pg_inode,
						   req->wb_context,
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

	/* no lseg means that pnfs is not in use, so no mirroring here */
	nfs_pageio_reset_write_mds(pgio);
out:
	return 1;
}