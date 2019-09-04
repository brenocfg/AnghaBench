#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  prev; } ;
struct nfs_pgio_mirror {scalar_t__ pg_count; TYPE_2__ pg_list; int /*<<< orphan*/  pg_base; } ;
struct nfs_pageio_descriptor {scalar_t__ pg_error; TYPE_1__* pg_ops; } ;
struct nfs_page {scalar_t__ wb_bytes; int /*<<< orphan*/  wb_pgbase; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* pg_init ) (struct nfs_pageio_descriptor*,struct nfs_page*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_can_coalesce_requests (struct nfs_page*,struct nfs_page*,struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_list_add_request (struct nfs_page*,TYPE_2__*) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 struct nfs_pgio_mirror* nfs_pgio_current_mirror (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pageio_descriptor*,struct nfs_page*) ; 

__attribute__((used)) static int nfs_pageio_do_add_request(struct nfs_pageio_descriptor *desc,
				     struct nfs_page *req)
{
	struct nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);

	struct nfs_page *prev = NULL;

	if (mirror->pg_count != 0) {
		prev = nfs_list_entry(mirror->pg_list.prev);
	} else {
		if (desc->pg_ops->pg_init)
			desc->pg_ops->pg_init(desc, req);
		if (desc->pg_error < 0)
			return 0;
		mirror->pg_base = req->wb_pgbase;
	}
	if (!nfs_can_coalesce_requests(prev, req, desc))
		return 0;
	nfs_list_remove_request(req);
	nfs_list_add_request(req, &mirror->pg_list);
	mirror->pg_count += req->wb_bytes;
	return 1;
}