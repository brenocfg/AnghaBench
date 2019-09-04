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
struct qm_eqcr {int busy; int available; TYPE_1__* cursor; } ;
struct TYPE_2__ {int /*<<< orphan*/  fqid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int QM_FQID_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void eqcr_commit_checks(struct qm_eqcr *eqcr)
{
	DPAA_ASSERT(eqcr->busy);
	DPAA_ASSERT(!(be32_to_cpu(eqcr->cursor->fqid) & ~QM_FQID_MASK));
	DPAA_ASSERT(eqcr->available >= 1);
}