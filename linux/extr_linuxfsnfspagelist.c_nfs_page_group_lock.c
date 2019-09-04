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
struct nfs_page {int /*<<< orphan*/  wb_flags; struct nfs_page* wb_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_CONTENDED1 ; 
 int /*<<< orphan*/  PG_HEADLOCK ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_on_bit_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nfs_page_group_lock(struct nfs_page *req)
{
	struct nfs_page *head = req->wb_head;

	WARN_ON_ONCE(head != head->wb_head);

	if (!test_and_set_bit(PG_HEADLOCK, &head->wb_flags))
		return 0;

	set_bit(PG_CONTENDED1, &head->wb_flags);
	smp_mb__after_atomic();
	return wait_on_bit_lock(&head->wb_flags, PG_HEADLOCK,
				TASK_UNINTERRUPTIBLE);
}