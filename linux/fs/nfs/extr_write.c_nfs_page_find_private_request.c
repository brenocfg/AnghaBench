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
struct nfs_page {int /*<<< orphan*/  wb_kref; struct nfs_page* wb_head; } ;
struct address_space {int /*<<< orphan*/  private_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct nfs_page* nfs_page_private_request (struct page*) ; 
 struct address_space* page_file_mapping (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs_page *
nfs_page_find_private_request(struct page *page)
{
	struct address_space *mapping = page_file_mapping(page);
	struct nfs_page *req;

	if (!PagePrivate(page))
		return NULL;
	spin_lock(&mapping->private_lock);
	req = nfs_page_private_request(page);
	if (req) {
		WARN_ON_ONCE(req->wb_head != req);
		kref_get(&req->wb_kref);
	}
	spin_unlock(&mapping->private_lock);
	return req;
}