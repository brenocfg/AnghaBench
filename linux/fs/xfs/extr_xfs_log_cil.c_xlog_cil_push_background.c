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
struct xlog {TYPE_1__* l_mp; struct xfs_cil* l_cilp; } ;
struct xfs_cil {scalar_t__ xc_push_seq; scalar_t__ xc_current_sequence; int /*<<< orphan*/  xc_push_lock; int /*<<< orphan*/  xc_push_work; TYPE_2__* xc_ctx; int /*<<< orphan*/  xc_cil; } ;
struct TYPE_4__ {scalar_t__ space_used; } ;
struct TYPE_3__ {int /*<<< orphan*/  m_cil_workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XLOG_CIL_SPACE_LIMIT (struct xlog*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xlog_cil_push_background(
	struct xlog	*log)
{
	struct xfs_cil	*cil = log->l_cilp;

	/*
	 * The cil won't be empty because we are called while holding the
	 * context lock so whatever we added to the CIL will still be there
	 */
	ASSERT(!list_empty(&cil->xc_cil));

	/*
	 * don't do a background push if we haven't used up all the
	 * space available yet.
	 */
	if (cil->xc_ctx->space_used < XLOG_CIL_SPACE_LIMIT(log))
		return;

	spin_lock(&cil->xc_push_lock);
	if (cil->xc_push_seq < cil->xc_current_sequence) {
		cil->xc_push_seq = cil->xc_current_sequence;
		queue_work(log->l_mp->m_cil_workqueue, &cil->xc_push_work);
	}
	spin_unlock(&cil->xc_push_lock);

}