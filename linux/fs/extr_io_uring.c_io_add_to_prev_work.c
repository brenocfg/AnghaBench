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
struct io_kiocb {int flags; int /*<<< orphan*/  list; } ;
struct async_list {int /*<<< orphan*/  lock; int /*<<< orphan*/  cnt; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int REQ_F_SEQ_PREV ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool io_add_to_prev_work(struct async_list *list, struct io_kiocb *req)
{
	bool ret;

	if (!list)
		return false;
	if (!(req->flags & REQ_F_SEQ_PREV))
		return false;
	if (!atomic_read(&list->cnt))
		return false;

	ret = true;
	spin_lock(&list->lock);
	list_add_tail(&req->list, &list->list);
	/*
	 * Ensure we see a simultaneous modification from io_sq_wq_submit_work()
	 */
	smp_mb();
	if (!atomic_read(&list->cnt)) {
		list_del_init(&req->list);
		ret = false;
	}
	spin_unlock(&list->lock);
	return ret;
}