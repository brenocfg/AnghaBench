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

/* Variables and functions */
 int /*<<< orphan*/  nfs_request_add_commit_list (struct nfs_page*,struct nfs_commit_info*) ; 
 scalar_t__ pnfs_mark_request_commit (struct nfs_page*,struct pnfs_layout_segment*,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 

void
nfs_mark_request_commit(struct nfs_page *req, struct pnfs_layout_segment *lseg,
			struct nfs_commit_info *cinfo, u32 ds_commit_idx)
{
	if (pnfs_mark_request_commit(req, lseg, cinfo, ds_commit_idx))
		return;
	nfs_request_add_commit_list(req, cinfo);
}