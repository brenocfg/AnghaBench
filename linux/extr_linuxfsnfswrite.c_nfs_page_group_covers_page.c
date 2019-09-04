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
struct nfs_page {unsigned int wb_pgbase; unsigned int wb_bytes; int /*<<< orphan*/  wb_head; int /*<<< orphan*/  wb_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_page_group_lock (struct nfs_page*) ; 
 struct nfs_page* nfs_page_group_search_locked (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nfs_page_group_unlock (struct nfs_page*) ; 
 unsigned int nfs_page_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nfs_page_group_covers_page(struct nfs_page *req)
{
	struct nfs_page *tmp;
	unsigned int pos = 0;
	unsigned int len = nfs_page_length(req->wb_page);

	nfs_page_group_lock(req);

	for (;;) {
		tmp = nfs_page_group_search_locked(req->wb_head, pos);
		if (!tmp)
			break;
		pos = tmp->wb_pgbase + tmp->wb_bytes;
	}

	nfs_page_group_unlock(req);
	return pos >= len;
}