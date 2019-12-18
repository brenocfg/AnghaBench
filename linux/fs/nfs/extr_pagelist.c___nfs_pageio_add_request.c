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
struct nfs_pgio_mirror {scalar_t__ pg_recoalesce; } ;
struct nfs_pageio_descriptor {int pg_moreio; scalar_t__ pg_error; } ;
struct nfs_page {unsigned int wb_bytes; unsigned int wb_offset; unsigned int wb_pgbase; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs_page*) ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ PTR_ERR (struct nfs_page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct nfs_page* nfs_create_subreq (struct nfs_page*,struct nfs_page*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nfs_page_group_lock (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_page_group_unlock (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_pageio_cleanup_request (struct nfs_pageio_descriptor*,struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_pageio_do_add_request (struct nfs_pageio_descriptor*,struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_pageio_doio (struct nfs_pageio_descriptor*) ; 
 struct nfs_pgio_mirror* nfs_pgio_current_mirror (struct nfs_pageio_descriptor*) ; 

__attribute__((used)) static int __nfs_pageio_add_request(struct nfs_pageio_descriptor *desc,
			   struct nfs_page *req)
{
	struct nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);

	struct nfs_page *subreq;
	unsigned int bytes_left = 0;
	unsigned int offset, pgbase;

	nfs_page_group_lock(req);

	subreq = req;
	bytes_left = subreq->wb_bytes;
	offset = subreq->wb_offset;
	pgbase = subreq->wb_pgbase;

	do {
		if (!nfs_pageio_do_add_request(desc, subreq)) {
			/* make sure pg_test call(s) did nothing */
			WARN_ON_ONCE(subreq->wb_bytes != bytes_left);
			WARN_ON_ONCE(subreq->wb_offset != offset);
			WARN_ON_ONCE(subreq->wb_pgbase != pgbase);

			nfs_page_group_unlock(req);
			desc->pg_moreio = 1;
			nfs_pageio_doio(desc);
			if (desc->pg_error < 0 || mirror->pg_recoalesce)
				goto out_cleanup_subreq;
			/* retry add_request for this subreq */
			nfs_page_group_lock(req);
			continue;
		}

		/* check for buggy pg_test call(s) */
		WARN_ON_ONCE(subreq->wb_bytes + subreq->wb_pgbase > PAGE_SIZE);
		WARN_ON_ONCE(subreq->wb_bytes > bytes_left);
		WARN_ON_ONCE(subreq->wb_bytes == 0);

		bytes_left -= subreq->wb_bytes;
		offset += subreq->wb_bytes;
		pgbase += subreq->wb_bytes;

		if (bytes_left) {
			subreq = nfs_create_subreq(req, subreq, pgbase,
					offset, bytes_left);
			if (IS_ERR(subreq))
				goto err_ptr;
		}
	} while (bytes_left > 0);

	nfs_page_group_unlock(req);
	return 1;
err_ptr:
	desc->pg_error = PTR_ERR(subreq);
	nfs_page_group_unlock(req);
	return 0;
out_cleanup_subreq:
	if (req != subreq)
		nfs_pageio_cleanup_request(desc, subreq);
	return 0;
}