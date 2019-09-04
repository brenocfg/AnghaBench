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
struct rm_atomic_op {scalar_t__ op_active; int /*<<< orphan*/ * op_notifier; int /*<<< orphan*/  op_sg; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 struct page* sg_page (int /*<<< orphan*/ ) ; 

void rds_atomic_free_op(struct rm_atomic_op *ao)
{
	struct page *page = sg_page(ao->op_sg);

	/* Mark page dirty if it was possibly modified, which
	 * is the case for a RDMA_READ which copies from remote
	 * to local memory */
	set_page_dirty(page);
	put_page(page);

	kfree(ao->op_notifier);
	ao->op_notifier = NULL;
	ao->op_active = 0;
}