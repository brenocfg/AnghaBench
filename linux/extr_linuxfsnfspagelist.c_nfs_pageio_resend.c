#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  next; } ;
struct nfs_pgio_header {TYPE_1__ pages; int /*<<< orphan*/  dreq; int /*<<< orphan*/  io_completion; } ;
struct nfs_pageio_descriptor {scalar_t__ pg_error; int /*<<< orphan*/  pg_dreq; int /*<<< orphan*/  pg_io_completion; } ;
struct nfs_page {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LIST_HEAD (TYPE_1__) ; 
 TYPE_1__ failed ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  list_move (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_list_add_request (struct nfs_page*,TYPE_1__*) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_pageio_add_request (struct nfs_pageio_descriptor*,struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_pageio_complete (struct nfs_pageio_descriptor*) ; 

int nfs_pageio_resend(struct nfs_pageio_descriptor *desc,
		      struct nfs_pgio_header *hdr)
{
	LIST_HEAD(failed);

	desc->pg_io_completion = hdr->io_completion;
	desc->pg_dreq = hdr->dreq;
	while (!list_empty(&hdr->pages)) {
		struct nfs_page *req = nfs_list_entry(hdr->pages.next);

		nfs_list_remove_request(req);
		if (!nfs_pageio_add_request(desc, req))
			nfs_list_add_request(req, &failed);
	}
	nfs_pageio_complete(desc);
	if (!list_empty(&failed)) {
		list_move(&failed, &hdr->pages);
		return desc->pg_error < 0 ? desc->pg_error : -EIO;
	}
	return 0;
}