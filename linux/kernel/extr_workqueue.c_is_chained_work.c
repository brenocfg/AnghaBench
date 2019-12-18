#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct workqueue_struct {int dummy; } ;
struct worker {TYPE_1__* current_pwq; } ;
struct TYPE_2__ {struct workqueue_struct* wq; } ;

/* Variables and functions */
 struct worker* current_wq_worker () ; 

__attribute__((used)) static bool is_chained_work(struct workqueue_struct *wq)
{
	struct worker *worker;

	worker = current_wq_worker();
	/*
	 * Return %true iff I'm a worker executing a work item on @wq.  If
	 * I'm @worker, it's safe to dereference it without locking.
	 */
	return worker && worker->current_pwq->wq == wq;
}