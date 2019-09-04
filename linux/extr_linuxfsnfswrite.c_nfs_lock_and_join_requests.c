#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct nfs_page {unsigned int wb_bytes; scalar_t__ wb_offset; int /*<<< orphan*/  wb_kref; int /*<<< orphan*/  wb_flags; struct nfs_page* wb_this_page; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nrequests; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 struct nfs_page* ERR_PTR (int) ; 
 TYPE_2__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  PG_INODE_REF ; 
 int /*<<< orphan*/  PG_REMOVE ; 
 scalar_t__ PagePrivate (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_clear_request_commit (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_destroy_unlinked_subrequests (struct nfs_page*,struct nfs_page*,struct inode*) ; 
 int /*<<< orphan*/  nfs_lock_request (struct nfs_page*) ; 
 struct nfs_page* nfs_page_find_head_request (struct page*) ; 
 int nfs_page_group_lock (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_page_group_unlock (struct nfs_page*) ; 
 struct nfs_page* nfs_page_private_request (struct page*) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_unlock_and_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_unroll_locks (struct inode*,struct nfs_page*,struct nfs_page*) ; 
 int nfs_wait_on_request (struct nfs_page*) ; 
 TYPE_1__* page_file_mapping (struct page*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs_page *
nfs_lock_and_join_requests(struct page *page)
{
	struct inode *inode = page_file_mapping(page)->host;
	struct nfs_page *head, *subreq;
	struct nfs_page *destroy_list = NULL;
	unsigned int total_bytes;
	int ret;

try_again:
	/*
	 * A reference is taken only on the head request which acts as a
	 * reference to the whole page group - the group will not be destroyed
	 * until the head reference is released.
	 */
	head = nfs_page_find_head_request(page);
	if (!head)
		return NULL;

	/* lock the page head first in order to avoid an ABBA inefficiency */
	if (!nfs_lock_request(head)) {
		ret = nfs_wait_on_request(head);
		nfs_release_request(head);
		if (ret < 0)
			return ERR_PTR(ret);
		goto try_again;
	}

	/* Ensure that nobody removed the request before we locked it */
	if (head != nfs_page_private_request(page) && !PageSwapCache(page)) {
		nfs_unlock_and_release_request(head);
		goto try_again;
	}

	ret = nfs_page_group_lock(head);
	if (ret < 0)
		goto release_request;

	/* lock each request in the page group */
	total_bytes = head->wb_bytes;
	for (subreq = head->wb_this_page; subreq != head;
			subreq = subreq->wb_this_page) {

		if (!kref_get_unless_zero(&subreq->wb_kref)) {
			if (subreq->wb_offset == head->wb_offset + total_bytes)
				total_bytes += subreq->wb_bytes;
			continue;
		}

		while (!nfs_lock_request(subreq)) {
			/*
			 * Unlock page to allow nfs_page_group_sync_on_bit()
			 * to succeed
			 */
			nfs_page_group_unlock(head);
			ret = nfs_wait_on_request(subreq);
			if (!ret)
				ret = nfs_page_group_lock(head);
			if (ret < 0) {
				nfs_unroll_locks(inode, head, subreq);
				nfs_release_request(subreq);
				goto release_request;
			}
		}
		/*
		 * Subrequests are always contiguous, non overlapping
		 * and in order - but may be repeated (mirrored writes).
		 */
		if (subreq->wb_offset == (head->wb_offset + total_bytes)) {
			/* keep track of how many bytes this group covers */
			total_bytes += subreq->wb_bytes;
		} else if (WARN_ON_ONCE(subreq->wb_offset < head->wb_offset ||
			    ((subreq->wb_offset + subreq->wb_bytes) >
			     (head->wb_offset + total_bytes)))) {
			nfs_page_group_unlock(head);
			nfs_unroll_locks(inode, head, subreq);
			nfs_unlock_and_release_request(subreq);
			ret = -EIO;
			goto release_request;
		}
	}

	/* Now that all requests are locked, make sure they aren't on any list.
	 * Commit list removal accounting is done after locks are dropped */
	subreq = head;
	do {
		nfs_clear_request_commit(subreq);
		subreq = subreq->wb_this_page;
	} while (subreq != head);

	/* unlink subrequests from head, destroy them later */
	if (head->wb_this_page != head) {
		/* destroy list will be terminated by head */
		destroy_list = head->wb_this_page;
		head->wb_this_page = head;

		/* change head request to cover whole range that
		 * the former page group covered */
		head->wb_bytes = total_bytes;
	}

	/* Postpone destruction of this request */
	if (test_and_clear_bit(PG_REMOVE, &head->wb_flags)) {
		set_bit(PG_INODE_REF, &head->wb_flags);
		kref_get(&head->wb_kref);
		atomic_long_inc(&NFS_I(inode)->nrequests);
	}

	nfs_page_group_unlock(head);

	nfs_destroy_unlinked_subrequests(destroy_list, head, inode);

	/* Did we lose a race with nfs_inode_remove_request()? */
	if (!(PagePrivate(page) || PageSwapCache(page))) {
		nfs_unlock_and_release_request(head);
		return NULL;
	}

	/* still holds ref on head from nfs_page_find_head_request
	 * and still has lock on head from lock loop */
	return head;

release_request:
	nfs_unlock_and_release_request(head);
	return ERR_PTR(ret);
}