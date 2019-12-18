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
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
nfs_page_group_unlock(struct nfs_page *req)
{
	struct nfs_page *head = req->wb_head;

	WARN_ON_ONCE(head != head->wb_head);

	smp_mb__before_atomic();
	clear_bit(PG_HEADLOCK, &head->wb_flags);
	smp_mb__after_atomic();
	if (!test_bit(PG_CONTENDED1, &head->wb_flags))
		return;
	wake_up_bit(&head->wb_flags, PG_HEADLOCK);
}