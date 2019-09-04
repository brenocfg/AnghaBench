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
 int /*<<< orphan*/  QM_CL_EQCR_CI_CENA ; 
 int /*<<< orphan*/  qm_cl_touch_ro (struct qm_portal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qm_eqcr_cce_prefetch(struct qm_portal *portal)
{
	qm_cl_touch_ro(portal, QM_CL_EQCR_CI_CENA);
}