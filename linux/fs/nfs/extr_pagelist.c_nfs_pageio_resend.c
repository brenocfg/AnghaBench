#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nfs_pgio_header {int /*<<< orphan*/  io_start; TYPE_1__* completion_ops; int /*<<< orphan*/  pages; int /*<<< orphan*/  dreq; int /*<<< orphan*/  io_completion; } ;
struct nfs_pageio_descriptor {int pg_error; int /*<<< orphan*/  pg_dreq; int /*<<< orphan*/  pg_io_completion; } ;
struct nfs_page {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  next; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* error_cleanup ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LIST_HEAD (TYPE_2__) ; 
 int /*<<< orphan*/  list_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,TYPE_2__*) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pageio_add_request (struct nfs_pageio_descriptor*,struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_pageio_complete (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_set_pgio_error (struct nfs_pgio_header*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ pages ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

int nfs_pageio_resend(struct nfs_pageio_descriptor *desc,
		      struct nfs_pgio_header *hdr)
{
	LIST_HEAD(pages);

	desc->pg_io_completion = hdr->io_completion;
	desc->pg_dreq = hdr->dreq;
	list_splice_init(&hdr->pages, &pages);
	while (!list_empty(&pages)) {
		struct nfs_page *req = nfs_list_entry(pages.next);

		if (!nfs_pageio_add_request(desc, req))
			break;
	}
	nfs_pageio_complete(desc);
	if (!list_empty(&pages)) {
		int err = desc->pg_error < 0 ? desc->pg_error : -EIO;
		hdr->completion_ops->error_cleanup(&pages, err);
		nfs_set_pgio_error(hdr, err, hdr->io_start);
		return err;
	}
	return 0;
}