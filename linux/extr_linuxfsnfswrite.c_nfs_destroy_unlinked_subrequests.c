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
struct nfs_page {int /*<<< orphan*/  wb_flags; struct nfs_page* wb_head; int /*<<< orphan*/  wb_kref; struct nfs_page* wb_this_page; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nrequests; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  PG_INODE_REF ; 
 int /*<<< orphan*/  PG_REMOVE ; 
 int /*<<< orphan*/  PG_TEARDOWN ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_free_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_unlock_and_release_request (struct nfs_page*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfs_destroy_unlinked_subrequests(struct nfs_page *destroy_list,
				 struct nfs_page *old_head,
				 struct inode *inode)
{
	while (destroy_list) {
		struct nfs_page *subreq = destroy_list;

		destroy_list = (subreq->wb_this_page == old_head) ?
				   NULL : subreq->wb_this_page;

		WARN_ON_ONCE(old_head != subreq->wb_head);

		/* make sure old group is not used */
		subreq->wb_this_page = subreq;

		clear_bit(PG_REMOVE, &subreq->wb_flags);

		/* Note: races with nfs_page_group_destroy() */
		if (!kref_read(&subreq->wb_kref)) {
			/* Check if we raced with nfs_page_group_destroy() */
			if (test_and_clear_bit(PG_TEARDOWN, &subreq->wb_flags))
				nfs_free_request(subreq);
			continue;
		}

		subreq->wb_head = subreq;

		if (test_and_clear_bit(PG_INODE_REF, &subreq->wb_flags)) {
			nfs_release_request(subreq);
			atomic_long_dec(&NFS_I(inode)->nrequests);
		}

		/* subreq is now totally disconnected from page group or any
		 * write / commit lists. last chance to wake any waiters */
		nfs_unlock_and_release_request(subreq);
	}
}