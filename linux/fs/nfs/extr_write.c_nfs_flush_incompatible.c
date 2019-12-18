#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct nfs_page {struct page* wb_page; struct nfs_lock_context* wb_lock_context; } ;
struct nfs_open_context {int dummy; } ;
struct nfs_lock_context {scalar_t__ lockowner; } ;
struct file_lock_context {int /*<<< orphan*/  flc_flock; int /*<<< orphan*/  flc_posix; } ;
struct file {int dummy; } ;
struct TYPE_6__ {scalar_t__ files; } ;
struct TYPE_5__ {struct file_lock_context* i_flctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 TYPE_3__* current ; 
 TYPE_2__* file_inode (struct file*) ; 
 scalar_t__ list_empty_careful (int /*<<< orphan*/ *) ; 
 struct nfs_open_context* nfs_file_open_context (struct file*) ; 
 int /*<<< orphan*/  nfs_match_open_context (int /*<<< orphan*/ ,struct nfs_open_context*) ; 
 struct nfs_page* nfs_page_find_head_request (struct page*) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_req_openctx (struct nfs_page*) ; 
 int nfs_wb_page (int /*<<< orphan*/ ,struct page*) ; 
 TYPE_1__* page_file_mapping (struct page*) ; 

int nfs_flush_incompatible(struct file *file, struct page *page)
{
	struct nfs_open_context *ctx = nfs_file_open_context(file);
	struct nfs_lock_context *l_ctx;
	struct file_lock_context *flctx = file_inode(file)->i_flctx;
	struct nfs_page	*req;
	int do_flush, status;
	/*
	 * Look for a request corresponding to this page. If there
	 * is one, and it belongs to another file, we flush it out
	 * before we try to copy anything into the page. Do this
	 * due to the lack of an ACCESS-type call in NFSv2.
	 * Also do the same if we find a request from an existing
	 * dropped page.
	 */
	do {
		req = nfs_page_find_head_request(page);
		if (req == NULL)
			return 0;
		l_ctx = req->wb_lock_context;
		do_flush = req->wb_page != page ||
			!nfs_match_open_context(nfs_req_openctx(req), ctx);
		if (l_ctx && flctx &&
		    !(list_empty_careful(&flctx->flc_posix) &&
		      list_empty_careful(&flctx->flc_flock))) {
			do_flush |= l_ctx->lockowner != current->files;
		}
		nfs_release_request(req);
		if (!do_flush)
			return 0;
		status = nfs_wb_page(page_file_mapping(page)->host, page);
	} while (status == 0);
	return status;
}