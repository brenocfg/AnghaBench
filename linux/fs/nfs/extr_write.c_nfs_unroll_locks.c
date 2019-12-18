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
struct nfs_page {int /*<<< orphan*/  wb_kref; struct nfs_page* wb_this_page; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_unlock_and_release_request (struct nfs_page*) ; 

__attribute__((used)) static void
nfs_unroll_locks(struct inode *inode, struct nfs_page *head,
			  struct nfs_page *req)
{
	struct nfs_page *tmp;

	/* relinquish all the locks successfully grabbed this run */
	for (tmp = head->wb_this_page ; tmp != req; tmp = tmp->wb_this_page) {
		if (!kref_read(&tmp->wb_kref))
			continue;
		nfs_unlock_and_release_request(tmp);
	}
}