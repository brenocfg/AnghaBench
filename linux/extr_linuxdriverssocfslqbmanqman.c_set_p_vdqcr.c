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
typedef  int /*<<< orphan*/  u32 ;
struct qman_portal {int /*<<< orphan*/  p; struct qman_fq* vdqcr_owned; } ;
struct qman_fq {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  QMAN_FQ_STATE_VDQCR ; 
 scalar_t__ fq_isset (struct qman_fq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fq_set (struct qman_fq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  qm_dqrr_vdqcr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_p_vdqcr(struct qman_portal *p, struct qman_fq *fq, u32 vdqcr)
{
	unsigned long irqflags;
	int ret = -EBUSY;

	local_irq_save(irqflags);
	if (p->vdqcr_owned)
		goto out;
	if (fq_isset(fq, QMAN_FQ_STATE_VDQCR))
		goto out;

	fq_set(fq, QMAN_FQ_STATE_VDQCR);
	p->vdqcr_owned = fq;
	qm_dqrr_vdqcr_set(&p->p, vdqcr);
	ret = 0;
out:
	local_irq_restore(irqflags);
	return ret;
}