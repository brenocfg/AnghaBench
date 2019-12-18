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
typedef  scalar_t__ u32 ;
struct nfs_pageio_descriptor {scalar_t__ pg_error; scalar_t__ pg_mirror_count; scalar_t__ pg_mirror_idx; } ;
struct nfs_page {unsigned int wb_pgbase; unsigned int wb_offset; unsigned int wb_bytes; struct nfs_page* wb_this_page; struct nfs_page* wb_head; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs_page*) ; 
 scalar_t__ PTR_ERR (struct nfs_page*) ; 
 struct nfs_page* nfs_create_subreq (struct nfs_page*,struct nfs_page*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nfs_page_group_lock (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_page_group_unlock (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_pageio_add_request_mirror (struct nfs_pageio_descriptor*,struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_pageio_cleanup_request (struct nfs_pageio_descriptor*,struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_pageio_error_cleanup (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_pageio_setup_mirroring (struct nfs_pageio_descriptor*,struct nfs_page*) ; 
 scalar_t__ nfs_pgio_has_mirroring (struct nfs_pageio_descriptor*) ; 

int nfs_pageio_add_request(struct nfs_pageio_descriptor *desc,
			   struct nfs_page *req)
{
	u32 midx;
	unsigned int pgbase, offset, bytes;
	struct nfs_page *dupreq, *lastreq;

	pgbase = req->wb_pgbase;
	offset = req->wb_offset;
	bytes = req->wb_bytes;

	nfs_pageio_setup_mirroring(desc, req);
	if (desc->pg_error < 0)
		goto out_failed;

	for (midx = 0; midx < desc->pg_mirror_count; midx++) {
		if (midx) {
			nfs_page_group_lock(req);

			/* find the last request */
			for (lastreq = req->wb_head;
			     lastreq->wb_this_page != req->wb_head;
			     lastreq = lastreq->wb_this_page)
				;

			dupreq = nfs_create_subreq(req, lastreq,
					pgbase, offset, bytes);

			nfs_page_group_unlock(req);
			if (IS_ERR(dupreq)) {
				desc->pg_error = PTR_ERR(dupreq);
				goto out_failed;
			}
		} else
			dupreq = req;

		if (nfs_pgio_has_mirroring(desc))
			desc->pg_mirror_idx = midx;
		if (!nfs_pageio_add_request_mirror(desc, dupreq))
			goto out_cleanup_subreq;
	}

	return 1;

out_cleanup_subreq:
	if (req != dupreq)
		nfs_pageio_cleanup_request(desc, dupreq);
out_failed:
	nfs_pageio_error_cleanup(desc);
	return 0;
}