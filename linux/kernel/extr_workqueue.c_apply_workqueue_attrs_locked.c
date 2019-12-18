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
struct workqueue_struct {int flags; int /*<<< orphan*/  pwqs; } ;
struct workqueue_attrs {int dummy; } ;
struct apply_wqattrs_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ WARN_ON (int) ; 
 int WQ_UNBOUND ; 
 int __WQ_ORDERED ; 
 int __WQ_ORDERED_EXPLICIT ; 
 int /*<<< orphan*/  apply_wqattrs_cleanup (struct apply_wqattrs_ctx*) ; 
 int /*<<< orphan*/  apply_wqattrs_commit (struct apply_wqattrs_ctx*) ; 
 struct apply_wqattrs_ctx* apply_wqattrs_prepare (struct workqueue_struct*,struct workqueue_attrs const*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apply_workqueue_attrs_locked(struct workqueue_struct *wq,
					const struct workqueue_attrs *attrs)
{
	struct apply_wqattrs_ctx *ctx;

	/* only unbound workqueues can change attributes */
	if (WARN_ON(!(wq->flags & WQ_UNBOUND)))
		return -EINVAL;

	/* creating multiple pwqs breaks ordering guarantee */
	if (!list_empty(&wq->pwqs)) {
		if (WARN_ON(wq->flags & __WQ_ORDERED_EXPLICIT))
			return -EINVAL;

		wq->flags &= ~__WQ_ORDERED;
	}

	ctx = apply_wqattrs_prepare(wq, attrs);
	if (!ctx)
		return -ENOMEM;

	/* the ctx has been prepared successfully, let's commit it */
	apply_wqattrs_commit(ctx);
	apply_wqattrs_cleanup(ctx);

	return 0;
}