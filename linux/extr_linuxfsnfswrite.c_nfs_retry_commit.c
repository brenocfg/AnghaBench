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
struct nfs_page {int /*<<< orphan*/  wb_page; } ;
struct nfs_commit_info {int /*<<< orphan*/  dreq; } ;
struct list_head {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  nfs_clear_page_commit (int /*<<< orphan*/ ) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_mark_request_commit (struct nfs_page*,struct pnfs_layout_segment*,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_unlock_and_release_request (struct nfs_page*) ; 

void nfs_retry_commit(struct list_head *page_list,
		      struct pnfs_layout_segment *lseg,
		      struct nfs_commit_info *cinfo,
		      u32 ds_commit_idx)
{
	struct nfs_page *req;

	while (!list_empty(page_list)) {
		req = nfs_list_entry(page_list->next);
		nfs_list_remove_request(req);
		nfs_mark_request_commit(req, lseg, cinfo, ds_commit_idx);
		if (!cinfo->dreq)
			nfs_clear_page_commit(req->wb_page);
		nfs_unlock_and_release_request(req);
	}
}