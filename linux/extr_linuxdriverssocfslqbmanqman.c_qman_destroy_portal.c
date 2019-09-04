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
struct qman_portal {struct qm_portal_config* config; int /*<<< orphan*/  p; int /*<<< orphan*/  cgrs; } ;
struct qm_portal_config {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct qman_portal*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_dqrr_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qm_dqrr_sdqcr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_eqcr_cce_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qm_eqcr_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qm_mc_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qm_mr_finish (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qman_destroy_portal(struct qman_portal *qm)
{
	const struct qm_portal_config *pcfg;

	/* Stop dequeues on the portal */
	qm_dqrr_sdqcr_set(&qm->p, 0);

	/*
	 * NB we do this to "quiesce" EQCR. If we add enqueue-completions or
	 * something related to QM_PIRQ_EQCI, this may need fixing.
	 * Also, due to the prefetching model used for CI updates in the enqueue
	 * path, this update will only invalidate the CI cacheline *after*
	 * working on it, so we need to call this twice to ensure a full update
	 * irrespective of where the enqueue processing was at when the teardown
	 * began.
	 */
	qm_eqcr_cce_update(&qm->p);
	qm_eqcr_cce_update(&qm->p);
	pcfg = qm->config;

	free_irq(pcfg->irq, qm);

	kfree(qm->cgrs);
	qm_mc_finish(&qm->p);
	qm_mr_finish(&qm->p);
	qm_dqrr_finish(&qm->p);
	qm_eqcr_finish(&qm->p);

	qm->config = NULL;
}