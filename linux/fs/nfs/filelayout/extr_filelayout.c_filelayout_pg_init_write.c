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
struct nfs_pageio_descriptor {int /*<<< orphan*/ * pg_lseg; int /*<<< orphan*/  pg_dreq; int /*<<< orphan*/  pg_inode; int /*<<< orphan*/  pg_error; } ;
struct nfs_page {int dummy; } ;
struct nfs_commit_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IOMODE_RW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS4_MAX_UINT64 ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int filelayout_alloc_commit_info (int /*<<< orphan*/ *,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fl_pnfs_update_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_init_cinfo (struct nfs_commit_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pageio_reset_write_mds (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_req_openctx (struct nfs_page*) ; 
 int /*<<< orphan*/  pnfs_generic_pg_check_layout (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  pnfs_put_lseg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
filelayout_pg_init_write(struct nfs_pageio_descriptor *pgio,
			 struct nfs_page *req)
{
	struct nfs_commit_info cinfo;
	int status;

	pnfs_generic_pg_check_layout(pgio);
	if (!pgio->pg_lseg) {
		pgio->pg_lseg = fl_pnfs_update_layout(pgio->pg_inode,
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
	status = filelayout_alloc_commit_info(pgio->pg_lseg, &cinfo, GFP_NOFS);
	if (status < 0) {
		pnfs_put_lseg(pgio->pg_lseg);
		pgio->pg_lseg = NULL;
		goto out_mds;
	}
	return;
out_mds:
	nfs_pageio_reset_write_mds(pgio);
}