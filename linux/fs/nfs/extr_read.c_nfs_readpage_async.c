#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct nfs_pgio_mirror {scalar_t__ pg_bytes_written; } ;
struct nfs_pageio_descriptor {scalar_t__ pg_error; int pg_mirror_count; struct nfs_pgio_mirror* pg_mirrors; } ;
struct nfs_page {int dummy; } ;
struct nfs_open_context {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  read_io; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs_page*) ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 unsigned int PAGE_SIZE ; 
 int PTR_ERR (struct nfs_page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  nfs_async_read_completion_ops ; 
 struct nfs_page* nfs_create_request (struct nfs_open_context*,struct page*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 unsigned int nfs_page_length (struct page*) ; 
 int /*<<< orphan*/  nfs_pageio_add_request (struct nfs_pageio_descriptor*,struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_pageio_complete (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_pageio_init_read (struct nfs_pageio_descriptor*,struct inode*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_readpage_release (struct nfs_page*,scalar_t__) ; 
 int nfs_return_empty_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,unsigned int) ; 

int nfs_readpage_async(struct nfs_open_context *ctx, struct inode *inode,
		       struct page *page)
{
	struct nfs_page	*new;
	unsigned int len;
	struct nfs_pageio_descriptor pgio;
	struct nfs_pgio_mirror *pgm;

	len = nfs_page_length(page);
	if (len == 0)
		return nfs_return_empty_page(page);
	new = nfs_create_request(ctx, page, 0, len);
	if (IS_ERR(new)) {
		unlock_page(page);
		return PTR_ERR(new);
	}
	if (len < PAGE_SIZE)
		zero_user_segment(page, len, PAGE_SIZE);

	nfs_pageio_init_read(&pgio, inode, false,
			     &nfs_async_read_completion_ops);
	if (!nfs_pageio_add_request(&pgio, new)) {
		nfs_list_remove_request(new);
		nfs_readpage_release(new, pgio.pg_error);
	}
	nfs_pageio_complete(&pgio);

	/* It doesn't make sense to do mirrored reads! */
	WARN_ON_ONCE(pgio.pg_mirror_count != 1);

	pgm = &pgio.pg_mirrors[0];
	NFS_I(inode)->read_io += pgm->pg_bytes_written;

	return pgio.pg_error < 0 ? pgio.pg_error : 0;
}