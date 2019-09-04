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
struct qm_portal {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void qm_dqrr_finish(struct qm_portal *portal)
{
#ifdef CONFIG_FSL_DPAA_CHECKING
	struct qm_dqrr *dqrr = &portal->dqrr;

	if (dqrr->cmode != qm_dqrr_cdc &&
	    dqrr->ci != dqrr_ptr2idx(dqrr->cursor))
		pr_crit("Ignoring completed DQRR entries\n");
#endif
}