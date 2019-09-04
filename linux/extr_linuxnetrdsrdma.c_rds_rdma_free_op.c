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
struct rm_rdma_op {unsigned int op_nents; scalar_t__ op_active; int /*<<< orphan*/ * op_notifier; int /*<<< orphan*/  op_write; int /*<<< orphan*/ * op_sg; } ;
struct page {int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 struct page* sg_page (int /*<<< orphan*/ *) ; 

void rds_rdma_free_op(struct rm_rdma_op *ro)
{
	unsigned int i;

	for (i = 0; i < ro->op_nents; i++) {
		struct page *page = sg_page(&ro->op_sg[i]);

		/* Mark page dirty if it was possibly modified, which
		 * is the case for a RDMA_READ which copies from remote
		 * to local memory */
		if (!ro->op_write) {
			WARN_ON(!page->mapping && irqs_disabled());
			set_page_dirty(page);
		}
		put_page(page);
	}

	kfree(ro->op_notifier);
	ro->op_notifier = NULL;
	ro->op_active = 0;
}