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
struct pool_workqueue {scalar_t__ nr_active; scalar_t__ max_active; int flush_color; TYPE_2__* wq; scalar_t__* nr_in_flight; int /*<<< orphan*/  delayed_works; } ;
struct TYPE_4__ {TYPE_1__* first_flusher; int /*<<< orphan*/  nr_pwqs_to_flush; } ;
struct TYPE_3__ {int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int WORK_NO_COLOR ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pwq (struct pool_workqueue*) ; 
 int /*<<< orphan*/  pwq_activate_first_delayed (struct pool_workqueue*) ; 

__attribute__((used)) static void pwq_dec_nr_in_flight(struct pool_workqueue *pwq, int color)
{
	/* uncolored work items don't participate in flushing or nr_active */
	if (color == WORK_NO_COLOR)
		goto out_put;

	pwq->nr_in_flight[color]--;

	pwq->nr_active--;
	if (!list_empty(&pwq->delayed_works)) {
		/* one down, submit a delayed one */
		if (pwq->nr_active < pwq->max_active)
			pwq_activate_first_delayed(pwq);
	}

	/* is flush in progress and are we at the flushing tip? */
	if (likely(pwq->flush_color != color))
		goto out_put;

	/* are there still in-flight works? */
	if (pwq->nr_in_flight[color])
		goto out_put;

	/* this pwq is done, clear flush_color */
	pwq->flush_color = -1;

	/*
	 * If this was the last pwq, wake up the first flusher.  It
	 * will handle the rest.
	 */
	if (atomic_dec_and_test(&pwq->wq->nr_pwqs_to_flush))
		complete(&pwq->wq->first_flusher->done);
out_put:
	put_pwq(pwq);
}