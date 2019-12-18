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
struct nfs_page {int dummy; } ;
struct nfs_open_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs_page*) ; 
 int PTR_ERR (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_grow_file (struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nfs_mark_request_dirty (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_mark_uptodate (struct nfs_page*) ; 
 struct nfs_page* nfs_setup_write_request (struct nfs_open_context*,struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nfs_unlock_and_release_request (struct nfs_page*) ; 

__attribute__((used)) static int nfs_writepage_setup(struct nfs_open_context *ctx, struct page *page,
		unsigned int offset, unsigned int count)
{
	struct nfs_page	*req;

	req = nfs_setup_write_request(ctx, page, offset, count);
	if (IS_ERR(req))
		return PTR_ERR(req);
	/* Update file length */
	nfs_grow_file(page, offset, count);
	nfs_mark_uptodate(req);
	nfs_mark_request_dirty(req);
	nfs_unlock_and_release_request(req);
	return 0;
}