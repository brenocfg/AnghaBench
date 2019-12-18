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
struct nfs_readdesc {TYPE_1__* pgio; int /*<<< orphan*/  ctx; } ;
struct nfs_page {int dummy; } ;
struct TYPE_2__ {int pg_error; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs_page*) ; 
 unsigned int PAGE_SIZE ; 
 int PTR_ERR (struct nfs_page*) ; 
 struct nfs_page* nfs_create_request (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 unsigned int nfs_page_length (struct page*) ; 
 int /*<<< orphan*/  nfs_pageio_add_request (TYPE_1__*,struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_readpage_release (struct nfs_page*,int) ; 
 int nfs_return_empty_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static int
readpage_async_filler(void *data, struct page *page)
{
	struct nfs_readdesc *desc = (struct nfs_readdesc *)data;
	struct nfs_page *new;
	unsigned int len;
	int error;

	len = nfs_page_length(page);
	if (len == 0)
		return nfs_return_empty_page(page);

	new = nfs_create_request(desc->ctx, page, 0, len);
	if (IS_ERR(new))
		goto out_error;

	if (len < PAGE_SIZE)
		zero_user_segment(page, len, PAGE_SIZE);
	if (!nfs_pageio_add_request(desc->pgio, new)) {
		nfs_list_remove_request(new);
		error = desc->pgio->pg_error;
		nfs_readpage_release(new, error);
		goto out;
	}
	return 0;
out_error:
	error = PTR_ERR(new);
	unlock_page(page);
out:
	return error;
}