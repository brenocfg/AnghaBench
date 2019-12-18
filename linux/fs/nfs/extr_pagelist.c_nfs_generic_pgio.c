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
struct page {int dummy; } ;
struct list_head {int /*<<< orphan*/  next; } ;
struct nfs_pgio_mirror {int /*<<< orphan*/  pg_count; int /*<<< orphan*/  pg_base; struct list_head pg_list; } ;
struct nfs_page_array {unsigned int npages; struct page** pagevec; struct page** page_array; } ;
struct nfs_pgio_header {int /*<<< orphan*/  pages; struct nfs_page_array page_array; } ;
struct nfs_pageio_descriptor {int pg_error; int pg_ioflags; int /*<<< orphan*/ * pg_rpc_callops; scalar_t__ pg_moreio; int /*<<< orphan*/  pg_dreq; int /*<<< orphan*/  pg_inode; } ;
struct nfs_page {struct page* wb_page; } ;
struct nfs_commit_info {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct page**) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FLUSH_COND_STABLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct page** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  nfs_init_cinfo (struct nfs_commit_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_list_move_request (struct nfs_page*,int /*<<< orphan*/ *) ; 
 unsigned int nfs_page_array_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pgio_common_ops ; 
 struct nfs_pgio_mirror* nfs_pgio_current_mirror (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_pgio_error (struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  nfs_pgio_rpcsetup (struct nfs_pgio_header*,int /*<<< orphan*/ ,int,struct nfs_commit_info*) ; 
 scalar_t__ nfs_reqs_to_commit (struct nfs_commit_info*) ; 

int nfs_generic_pgio(struct nfs_pageio_descriptor *desc,
		     struct nfs_pgio_header *hdr)
{
	struct nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);

	struct nfs_page		*req;
	struct page		**pages,
				*last_page;
	struct list_head *head = &mirror->pg_list;
	struct nfs_commit_info cinfo;
	struct nfs_page_array *pg_array = &hdr->page_array;
	unsigned int pagecount, pageused;
	gfp_t gfp_flags = GFP_KERNEL;

	pagecount = nfs_page_array_len(mirror->pg_base, mirror->pg_count);
	pg_array->npages = pagecount;

	if (pagecount <= ARRAY_SIZE(pg_array->page_array))
		pg_array->pagevec = pg_array->page_array;
	else {
		pg_array->pagevec = kcalloc(pagecount, sizeof(struct page *), gfp_flags);
		if (!pg_array->pagevec) {
			pg_array->npages = 0;
			nfs_pgio_error(hdr);
			desc->pg_error = -ENOMEM;
			return desc->pg_error;
		}
	}

	nfs_init_cinfo(&cinfo, desc->pg_inode, desc->pg_dreq);
	pages = hdr->page_array.pagevec;
	last_page = NULL;
	pageused = 0;
	while (!list_empty(head)) {
		req = nfs_list_entry(head->next);
		nfs_list_move_request(req, &hdr->pages);

		if (!last_page || last_page != req->wb_page) {
			pageused++;
			if (pageused > pagecount)
				break;
			*pages++ = last_page = req->wb_page;
		}
	}
	if (WARN_ON_ONCE(pageused != pagecount)) {
		nfs_pgio_error(hdr);
		desc->pg_error = -EINVAL;
		return desc->pg_error;
	}

	if ((desc->pg_ioflags & FLUSH_COND_STABLE) &&
	    (desc->pg_moreio || nfs_reqs_to_commit(&cinfo)))
		desc->pg_ioflags &= ~FLUSH_COND_STABLE;

	/* Set up the argument struct */
	nfs_pgio_rpcsetup(hdr, mirror->pg_count, desc->pg_ioflags, &cinfo);
	desc->pg_rpc_callops = &nfs_pgio_common_ops;
	return 0;
}