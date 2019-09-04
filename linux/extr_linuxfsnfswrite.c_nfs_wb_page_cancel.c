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
struct inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs_page*) ; 
 int PTR_ERR (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_inode_remove_request (struct nfs_page*) ; 
 struct nfs_page* nfs_lock_and_join_requests (struct page*) ; 
 int /*<<< orphan*/  nfs_unlock_and_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

int nfs_wb_page_cancel(struct inode *inode, struct page *page)
{
	struct nfs_page *req;
	int ret = 0;

	wait_on_page_writeback(page);

	/* blocking call to cancel all requests and join to a single (head)
	 * request */
	req = nfs_lock_and_join_requests(page);

	if (IS_ERR(req)) {
		ret = PTR_ERR(req);
	} else if (req) {
		/* all requests from this page have been cancelled by
		 * nfs_lock_and_join_requests, so just remove the head
		 * request from the inode / page_private pointer and
		 * release it */
		nfs_inode_remove_request(req);
		nfs_unlock_and_release_request(req);
	}

	return ret;
}