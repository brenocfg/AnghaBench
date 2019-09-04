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
struct TYPE_4__ {int /*<<< orphan*/  available; struct dpaa2_dq const* storage; } ;
struct qbman_swp {TYPE_2__ vdq; } ;
struct TYPE_3__ {scalar_t__ tok; } ;
struct dpaa2_dq {TYPE_1__ dq; } ;

/* Variables and functions */
 scalar_t__ QMAN_DQ_TOKEN_VALID ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

int qbman_result_has_new_result(struct qbman_swp *s, const struct dpaa2_dq *dq)
{
	if (dq->dq.tok != QMAN_DQ_TOKEN_VALID)
		return 0;

	/*
	 * Set token to be 0 so we will detect change back to 1
	 * next time the looping is traversed. Const is cast away here
	 * as we want users to treat the dequeue responses as read only.
	 */
	((struct dpaa2_dq *)dq)->dq.tok = 0;

	/*
	 * Determine whether VDQCR is available based on whether the
	 * current result is sitting in the first storage location of
	 * the busy command.
	 */
	if (s->vdq.storage == dq) {
		s->vdq.storage = NULL;
		atomic_inc(&s->vdq.available);
	}

	return 1;
}