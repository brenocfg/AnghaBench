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
typedef  int /*<<< orphan*/  u64 ;
struct nfs_pageio_descriptor {int /*<<< orphan*/ * pg_lseg; int /*<<< orphan*/  pg_error; int /*<<< orphan*/  pg_inode; } ;
struct nfs_page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IOMODE_RW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_pageio_reset_write_mds (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_req_openctx (struct nfs_page*) ; 
 int /*<<< orphan*/  pnfs_generic_pg_check_layout (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  pnfs_generic_pg_check_range (struct nfs_pageio_descriptor*,struct nfs_page*) ; 
 int /*<<< orphan*/ * pnfs_update_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_offset (struct nfs_page*) ; 

void
pnfs_generic_pg_init_write(struct nfs_pageio_descriptor *pgio,
			   struct nfs_page *req, u64 wb_size)
{
	pnfs_generic_pg_check_layout(pgio);
	pnfs_generic_pg_check_range(pgio, req);
	if (pgio->pg_lseg == NULL) {
		pgio->pg_lseg = pnfs_update_layout(pgio->pg_inode,
						   nfs_req_openctx(req),
						   req_offset(req),
						   wb_size,
						   IOMODE_RW,
						   false,
						   GFP_KERNEL);
		if (IS_ERR(pgio->pg_lseg)) {
			pgio->pg_error = PTR_ERR(pgio->pg_lseg);
			pgio->pg_lseg = NULL;
			return;
		}
	}
	/* If no lseg, fall back to write through mds */
	if (pgio->pg_lseg == NULL)
		nfs_pageio_reset_write_mds(pgio);
}