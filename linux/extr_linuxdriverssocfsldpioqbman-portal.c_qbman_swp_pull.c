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
struct TYPE_2__ {int valid_bit; void* storage; int /*<<< orphan*/  available; } ;
struct qbman_swp {TYPE_1__ vdq; } ;
struct qbman_pull_desc {int verb; scalar_t__ rsp_addr_virt; int /*<<< orphan*/  rsp_addr; int /*<<< orphan*/  dq_src; int /*<<< orphan*/  tok; int /*<<< orphan*/  numf; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  QBMAN_CENA_SWP_VDQCR ; 
 int QB_VALID_BIT ; 
 int /*<<< orphan*/  QMAN_DQ_TOKEN_VALID ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 struct qbman_pull_desc* qbman_get_cmd (struct qbman_swp*,int /*<<< orphan*/ ) ; 

int qbman_swp_pull(struct qbman_swp *s, struct qbman_pull_desc *d)
{
	struct qbman_pull_desc *p;

	if (!atomic_dec_and_test(&s->vdq.available)) {
		atomic_inc(&s->vdq.available);
		return -EBUSY;
	}
	s->vdq.storage = (void *)(uintptr_t)d->rsp_addr_virt;
	p = qbman_get_cmd(s, QBMAN_CENA_SWP_VDQCR);
	p->numf = d->numf;
	p->tok = QMAN_DQ_TOKEN_VALID;
	p->dq_src = d->dq_src;
	p->rsp_addr = d->rsp_addr;
	p->rsp_addr_virt = d->rsp_addr_virt;
	dma_wmb();

	/* Set the verb byte, have to substitute in the valid-bit */
	p->verb = d->verb | s->vdq.valid_bit;
	s->vdq.valid_bit ^= QB_VALID_BIT;

	return 0;
}