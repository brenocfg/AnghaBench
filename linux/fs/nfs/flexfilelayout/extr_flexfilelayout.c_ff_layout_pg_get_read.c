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
struct nfs_page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IOMODE_READ ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS4_MAX_UINT64 ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_req_openctx (struct nfs_page*) ; 
 int /*<<< orphan*/  pnfs_put_lseg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pnfs_update_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ff_layout_pg_get_read(struct nfs_pageio_descriptor *pgio,
		      struct nfs_page *req,
		      bool strict_iomode)
{
	pnfs_put_lseg(pgio->pg_lseg);
	pgio->pg_lseg = pnfs_update_layout(pgio->pg_inode,
					   nfs_req_openctx(req),
					   0,
					   NFS4_MAX_UINT64,
					   IOMODE_READ,
					   strict_iomode,
					   GFP_KERNEL);
	if (IS_ERR(pgio->pg_lseg)) {
		pgio->pg_error = PTR_ERR(pgio->pg_lseg);
		pgio->pg_lseg = NULL;
	}
}