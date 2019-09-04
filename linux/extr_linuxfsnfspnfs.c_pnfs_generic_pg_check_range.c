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
struct nfs_pageio_descriptor {int /*<<< orphan*/ * pg_lseg; } ;
struct nfs_page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pnfs_lseg_request_intersecting (int /*<<< orphan*/ *,struct nfs_page*) ; 
 int /*<<< orphan*/  pnfs_put_lseg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pnfs_generic_pg_check_range(struct nfs_pageio_descriptor *pgio, struct nfs_page *req)
{
	if (pgio->pg_lseg && !pnfs_lseg_request_intersecting(pgio->pg_lseg, req)) {
		pnfs_put_lseg(pgio->pg_lseg);
		pgio->pg_lseg = NULL;
	}
}