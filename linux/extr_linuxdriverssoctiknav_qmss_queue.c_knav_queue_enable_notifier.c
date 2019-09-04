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
struct knav_queue_inst {int /*<<< orphan*/  num_notifiers; } ;
struct knav_queue {int /*<<< orphan*/  notifier_enabled; int /*<<< orphan*/  notifier_fn; struct knav_queue_inst* inst; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knav_queue_set_notify (struct knav_queue_inst*,int) ; 

__attribute__((used)) static int knav_queue_enable_notifier(struct knav_queue *qh)
{
	struct knav_queue_inst *inst = qh->inst;
	bool first;

	if (WARN_ON(!qh->notifier_fn))
		return -EINVAL;

	/* Adjust the per handle notifier count */
	first = (atomic_inc_return(&qh->notifier_enabled) == 1);
	if (!first)
		return 0; /* nothing to do */

	/* Now adjust the per instance notifier count */
	first = (atomic_inc_return(&inst->num_notifiers) == 1);
	if (first)
		knav_queue_set_notify(inst, true);

	return 0;
}