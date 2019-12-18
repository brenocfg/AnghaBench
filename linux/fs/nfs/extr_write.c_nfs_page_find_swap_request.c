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
struct nfs_page {int /*<<< orphan*/  wb_kref; struct nfs_page* wb_head; } ;
struct nfs_inode {int /*<<< orphan*/  commit_mutex; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nfs_page* nfs_page_search_commits_for_head_request_locked (struct nfs_inode*,struct page*) ; 
 TYPE_1__* page_file_mapping (struct page*) ; 

__attribute__((used)) static struct nfs_page *
nfs_page_find_swap_request(struct page *page)
{
	struct inode *inode = page_file_mapping(page)->host;
	struct nfs_inode *nfsi = NFS_I(inode);
	struct nfs_page *req = NULL;
	if (!PageSwapCache(page))
		return NULL;
	mutex_lock(&nfsi->commit_mutex);
	if (PageSwapCache(page)) {
		req = nfs_page_search_commits_for_head_request_locked(nfsi,
			page);
		if (req) {
			WARN_ON_ONCE(req->wb_head != req);
			kref_get(&req->wb_kref);
		}
	}
	mutex_unlock(&nfsi->commit_mutex);
	return req;
}