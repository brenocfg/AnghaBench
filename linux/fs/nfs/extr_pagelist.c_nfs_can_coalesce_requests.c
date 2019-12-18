#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nfs_pageio_descriptor {TYPE_1__* pg_ops; } ;
struct nfs_page {scalar_t__ wb_bytes; scalar_t__ wb_page; scalar_t__ wb_pgbase; int /*<<< orphan*/  wb_lock_context; } ;
struct file_lock_context {int /*<<< orphan*/  flc_flock; int /*<<< orphan*/  flc_posix; } ;
struct TYPE_8__ {struct file_lock_context* i_flctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  dentry; } ;
struct TYPE_6__ {size_t (* pg_test ) (struct nfs_pageio_descriptor*,struct nfs_page*,struct nfs_page*) ;} ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 TYPE_5__* d_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty_careful (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_match_lock_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_match_open_context (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* nfs_req_openctx (struct nfs_page*) ; 
 scalar_t__ req_offset (struct nfs_page*) ; 
 size_t stub1 (struct nfs_pageio_descriptor*,struct nfs_page*,struct nfs_page*) ; 

__attribute__((used)) static bool nfs_can_coalesce_requests(struct nfs_page *prev,
				      struct nfs_page *req,
				      struct nfs_pageio_descriptor *pgio)
{
	size_t size;
	struct file_lock_context *flctx;

	if (prev) {
		if (!nfs_match_open_context(nfs_req_openctx(req), nfs_req_openctx(prev)))
			return false;
		flctx = d_inode(nfs_req_openctx(req)->dentry)->i_flctx;
		if (flctx != NULL &&
		    !(list_empty_careful(&flctx->flc_posix) &&
		      list_empty_careful(&flctx->flc_flock)) &&
		    !nfs_match_lock_context(req->wb_lock_context,
					    prev->wb_lock_context))
			return false;
		if (req_offset(req) != req_offset(prev) + prev->wb_bytes)
			return false;
		if (req->wb_page == prev->wb_page) {
			if (req->wb_pgbase != prev->wb_pgbase + prev->wb_bytes)
				return false;
		} else {
			if (req->wb_pgbase != 0 ||
			    prev->wb_pgbase + prev->wb_bytes != PAGE_SIZE)
				return false;
		}
	}
	size = pgio->pg_ops->pg_test(pgio, prev, req);
	WARN_ON_ONCE(size > req->wb_bytes);
	if (size && size < req->wb_bytes)
		req->wb_bytes = size;
	return size > 0;
}