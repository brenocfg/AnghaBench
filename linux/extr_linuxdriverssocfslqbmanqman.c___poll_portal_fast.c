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
struct qman_portal {int /*<<< orphan*/  p; struct qman_fq* vdqcr_owned; } ;
struct TYPE_2__ {int (* dqrr ) (struct qman_portal*,struct qman_fq*,struct qm_dqrr_entry const*) ;} ;
struct qman_fq {TYPE_1__ cb; } ;
struct qm_dqrr_entry {int stat; int /*<<< orphan*/  context_b; } ;
typedef  enum qman_cb_dqrr_result { ____Placeholder_qman_cb_dqrr_result } qman_cb_dqrr_result ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int /*<<< orphan*/  QMAN_FQ_STATE_NE ; 
 int QM_DQRR_STAT_DQCR_EXPIRED ; 
 int QM_DQRR_STAT_FQ_EMPTY ; 
 int QM_DQRR_STAT_FQ_HELDACTIVE ; 
 int QM_DQRR_STAT_UNSCHEDULED ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_vdqcr (struct qman_portal*,struct qman_fq*) ; 
 int /*<<< orphan*/  fq_clear (struct qman_fq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_dqrr_cdc_consume_1ptr (int /*<<< orphan*/ *,struct qm_dqrr_entry const*,int) ; 
 struct qm_dqrr_entry* qm_dqrr_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qm_dqrr_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qm_dqrr_pvb_update (int /*<<< orphan*/ *) ; 
 int qman_cb_dqrr_consume_stop ; 
 int qman_cb_dqrr_defer ; 
 int qman_cb_dqrr_park ; 
 int qman_cb_dqrr_stop ; 
 int stub1 (struct qman_portal*,struct qman_fq*,struct qm_dqrr_entry const*) ; 
 int stub2 (struct qman_portal*,struct qman_fq*,struct qm_dqrr_entry const*) ; 
 struct qman_fq* tag_to_fq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int __poll_portal_fast(struct qman_portal *p,
					unsigned int poll_limit)
{
	const struct qm_dqrr_entry *dq;
	struct qman_fq *fq;
	enum qman_cb_dqrr_result res;
	unsigned int limit = 0;

	do {
		qm_dqrr_pvb_update(&p->p);
		dq = qm_dqrr_current(&p->p);
		if (!dq)
			break;

		if (dq->stat & QM_DQRR_STAT_UNSCHEDULED) {
			/*
			 * VDQCR: don't trust context_b as the FQ may have
			 * been configured for h/w consumption and we're
			 * draining it post-retirement.
			 */
			fq = p->vdqcr_owned;
			/*
			 * We only set QMAN_FQ_STATE_NE when retiring, so we
			 * only need to check for clearing it when doing
			 * volatile dequeues.  It's one less thing to check
			 * in the critical path (SDQCR).
			 */
			if (dq->stat & QM_DQRR_STAT_FQ_EMPTY)
				fq_clear(fq, QMAN_FQ_STATE_NE);
			/*
			 * This is duplicated from the SDQCR code, but we
			 * have stuff to do before *and* after this callback,
			 * and we don't want multiple if()s in the critical
			 * path (SDQCR).
			 */
			res = fq->cb.dqrr(p, fq, dq);
			if (res == qman_cb_dqrr_stop)
				break;
			/* Check for VDQCR completion */
			if (dq->stat & QM_DQRR_STAT_DQCR_EXPIRED)
				clear_vdqcr(p, fq);
		} else {
			/* SDQCR: context_b points to the FQ */
			fq = tag_to_fq(be32_to_cpu(dq->context_b));
			/* Now let the callback do its stuff */
			res = fq->cb.dqrr(p, fq, dq);
			/*
			 * The callback can request that we exit without
			 * consuming this entry nor advancing;
			 */
			if (res == qman_cb_dqrr_stop)
				break;
		}
		/* Interpret 'dq' from a driver perspective. */
		/*
		 * Parking isn't possible unless HELDACTIVE was set. NB,
		 * FORCEELIGIBLE implies HELDACTIVE, so we only need to
		 * check for HELDACTIVE to cover both.
		 */
		DPAA_ASSERT((dq->stat & QM_DQRR_STAT_FQ_HELDACTIVE) ||
			    (res != qman_cb_dqrr_park));
		/* just means "skip it, I'll consume it myself later on" */
		if (res != qman_cb_dqrr_defer)
			qm_dqrr_cdc_consume_1ptr(&p->p, dq,
						 res == qman_cb_dqrr_park);
		/* Move forward */
		qm_dqrr_next(&p->p);
		/*
		 * Entry processed and consumed, increment our counter.  The
		 * callback can request that we exit after consuming the
		 * entry, and we also exit if we reach our processing limit,
		 * so loop back only if neither of these conditions is met.
		 */
	} while (++limit < poll_limit && res != qman_cb_dqrr_consume_stop);

	return limit;
}