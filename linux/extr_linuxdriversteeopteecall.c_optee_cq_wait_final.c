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
struct optee_call_waiter {int /*<<< orphan*/  c; int /*<<< orphan*/  list_node; } ;
struct optee_call_queue {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 scalar_t__ completion_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optee_cq_complete_one (struct optee_call_queue*) ; 

__attribute__((used)) static void optee_cq_wait_final(struct optee_call_queue *cq,
				struct optee_call_waiter *w)
{
	/*
	 * We're done with the call to secure world. The thread in secure
	 * world that was used for this call is now available for some
	 * other task to use.
	 */
	mutex_lock(&cq->mutex);

	/* Get out of the list */
	list_del(&w->list_node);

	/* Wake up one eventual waiting task */
	optee_cq_complete_one(cq);

	/*
	 * If we're completed we've got a completion from another task that
	 * was just done with its call to secure world. Since yet another
	 * thread now is available in secure world wake up another eventual
	 * waiting task.
	 */
	if (completion_done(&w->c))
		optee_cq_complete_one(cq);

	mutex_unlock(&cq->mutex);
}