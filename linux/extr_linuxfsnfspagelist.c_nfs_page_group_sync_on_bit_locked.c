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
struct nfs_page {struct nfs_page* wb_this_page; int /*<<< orphan*/  wb_flags; struct nfs_page* wb_head; } ;

/* Variables and functions */
 unsigned int PG_HEADLOCK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int test_and_set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
nfs_page_group_sync_on_bit_locked(struct nfs_page *req, unsigned int bit)
{
	struct nfs_page *head = req->wb_head;
	struct nfs_page *tmp;

	WARN_ON_ONCE(!test_bit(PG_HEADLOCK, &head->wb_flags));
	WARN_ON_ONCE(test_and_set_bit(bit, &req->wb_flags));

	tmp = req->wb_this_page;
	while (tmp != req) {
		if (!test_bit(bit, &tmp->wb_flags))
			return false;
		tmp = tmp->wb_this_page;
	}

	/* true! reset all bits */
	tmp = req;
	do {
		clear_bit(bit, &tmp->wb_flags);
		tmp = tmp->wb_this_page;
	} while (tmp != req);

	return true;
}