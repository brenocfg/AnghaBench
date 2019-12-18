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
struct nfs_page {int /*<<< orphan*/  wb_kref; int /*<<< orphan*/  wb_flags; int /*<<< orphan*/  wb_page; struct nfs_page* wb_head; struct nfs_page* wb_this_page; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nrequests; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 TYPE_2__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  PG_HEADLOCK ; 
 int /*<<< orphan*/  PG_INODE_REF ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 TYPE_1__* page_file_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
nfs_page_group_init(struct nfs_page *req, struct nfs_page *prev)
{
	struct inode *inode;
	WARN_ON_ONCE(prev == req);

	if (!prev) {
		/* a head request */
		req->wb_head = req;
		req->wb_this_page = req;
	} else {
		/* a subrequest */
		WARN_ON_ONCE(prev->wb_this_page != prev->wb_head);
		WARN_ON_ONCE(!test_bit(PG_HEADLOCK, &prev->wb_head->wb_flags));
		req->wb_head = prev->wb_head;
		req->wb_this_page = prev->wb_this_page;
		prev->wb_this_page = req;

		/* All subrequests take a ref on the head request until
		 * nfs_page_group_destroy is called */
		kref_get(&req->wb_head->wb_kref);

		/* grab extra ref and bump the request count if head request
		 * has extra ref from the write/commit path to handle handoff
		 * between write and commit lists. */
		if (test_bit(PG_INODE_REF, &prev->wb_head->wb_flags)) {
			inode = page_file_mapping(req->wb_page)->host;
			set_bit(PG_INODE_REF, &req->wb_flags);
			kref_get(&req->wb_kref);
			atomic_long_inc(&NFS_I(inode)->nrequests);
		}
	}
}