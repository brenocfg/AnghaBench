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
typedef  int /*<<< orphan*/  u32 ;
struct pnfs_layout_segment {int dummy; } ;
struct nfs_page {int dummy; } ;
struct nfs_commit_info {int dummy; } ;
struct nfs4_filelayout_segment {scalar_t__ commit_through_mds; } ;

/* Variables and functions */
 struct nfs4_filelayout_segment* FILELAYOUT_LSEG (struct pnfs_layout_segment*) ; 
 int /*<<< orphan*/  nfs4_fl_calc_j_index (struct pnfs_layout_segment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_request_add_commit_list (struct nfs_page*,struct nfs_commit_info*) ; 
 int /*<<< orphan*/  pnfs_layout_mark_request_commit (struct nfs_page*,struct pnfs_layout_segment*,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_offset (struct nfs_page*) ; 
 int /*<<< orphan*/  select_bucket_index (struct nfs4_filelayout_segment*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
filelayout_mark_request_commit(struct nfs_page *req,
			       struct pnfs_layout_segment *lseg,
			       struct nfs_commit_info *cinfo,
			       u32 ds_commit_idx)

{
	struct nfs4_filelayout_segment *fl = FILELAYOUT_LSEG(lseg);
	u32 i, j;

	if (fl->commit_through_mds) {
		nfs_request_add_commit_list(req, cinfo);
	} else {
		/* Note that we are calling nfs4_fl_calc_j_index on each page
		 * that ends up being committed to a data server.  An attractive
		 * alternative is to add a field to nfs_write_data and nfs_page
		 * to store the value calculated in filelayout_write_pagelist
		 * and just use that here.
		 */
		j = nfs4_fl_calc_j_index(lseg, req_offset(req));
		i = select_bucket_index(fl, j);
		pnfs_layout_mark_request_commit(req, lseg, cinfo, i);
	}
}