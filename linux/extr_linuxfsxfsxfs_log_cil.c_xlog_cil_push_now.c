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
typedef  scalar_t__ xfs_lsn_t ;
struct xlog {TYPE_1__* l_mp; struct xfs_cil* l_cilp; } ;
struct xfs_cil {scalar_t__ xc_current_sequence; scalar_t__ xc_push_seq; int /*<<< orphan*/  xc_push_lock; int /*<<< orphan*/  xc_push_work; int /*<<< orphan*/  xc_cil; } ;
struct TYPE_2__ {int /*<<< orphan*/  m_cil_workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xlog_cil_push_now(
	struct xlog	*log,
	xfs_lsn_t	push_seq)
{
	struct xfs_cil	*cil = log->l_cilp;

	if (!cil)
		return;

	ASSERT(push_seq && push_seq <= cil->xc_current_sequence);

	/* start on any pending background push to minimise wait time on it */
	flush_work(&cil->xc_push_work);

	/*
	 * If the CIL is empty or we've already pushed the sequence then
	 * there's no work we need to do.
	 */
	spin_lock(&cil->xc_push_lock);
	if (list_empty(&cil->xc_cil) || push_seq <= cil->xc_push_seq) {
		spin_unlock(&cil->xc_push_lock);
		return;
	}

	cil->xc_push_seq = push_seq;
	queue_work(log->l_mp->m_cil_workqueue, &cil->xc_push_work);
	spin_unlock(&cil->xc_push_lock);
}