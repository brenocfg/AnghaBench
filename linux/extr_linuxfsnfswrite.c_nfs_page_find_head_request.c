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

/* Variables and functions */
 struct nfs_page* nfs_page_find_private_request (struct page*) ; 
 struct nfs_page* nfs_page_find_swap_request (struct page*) ; 

__attribute__((used)) static struct nfs_page *nfs_page_find_head_request(struct page *page)
{
	struct nfs_page *req;

	req = nfs_page_find_private_request(page);
	if (!req)
		req = nfs_page_find_swap_request(page);
	return req;
}