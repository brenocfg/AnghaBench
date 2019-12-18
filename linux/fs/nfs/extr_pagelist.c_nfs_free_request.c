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
struct nfs_page {int /*<<< orphan*/  wb_flags; struct nfs_page* wb_this_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_REMOVE ; 
 int /*<<< orphan*/  PG_TEARDOWN ; 
 int /*<<< orphan*/  PG_UNLOCKPAGE ; 
 int /*<<< orphan*/  PG_UPTODATE ; 
 int /*<<< orphan*/  PG_WB_END ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  nfs_clear_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_page_free (struct nfs_page*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nfs_free_request(struct nfs_page *req)
{
	WARN_ON_ONCE(req->wb_this_page != req);

	/* extra debug: make sure no sync bits are still set */
	WARN_ON_ONCE(test_bit(PG_TEARDOWN, &req->wb_flags));
	WARN_ON_ONCE(test_bit(PG_UNLOCKPAGE, &req->wb_flags));
	WARN_ON_ONCE(test_bit(PG_UPTODATE, &req->wb_flags));
	WARN_ON_ONCE(test_bit(PG_WB_END, &req->wb_flags));
	WARN_ON_ONCE(test_bit(PG_REMOVE, &req->wb_flags));

	/* Release struct file and open context */
	nfs_clear_request(req);
	nfs_page_free(req);
}