#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct qbman_swp_desc {int qman_version; int /*<<< orphan*/  cinh_bar; int /*<<< orphan*/  cena_bar; } ;
struct TYPE_6__ {int dqrr_size; int reset_bug; void* valid_bit; scalar_t__ next_idx; } ;
struct TYPE_5__ {void* valid_bit; int /*<<< orphan*/  available; } ;
struct TYPE_4__ {void* valid_bit; } ;
struct qbman_swp {int sdq; TYPE_3__ dqrr; int /*<<< orphan*/  addr_cinh; int /*<<< orphan*/  addr_cena; struct qbman_swp_desc const* desc; TYPE_2__ vdq; TYPE_1__ mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QBMAN_CINH_SWP_CFG ; 
 int /*<<< orphan*/  QBMAN_CINH_SWP_SDQCR ; 
 int QB_SDQCR_DCT_SHIFT ; 
 int QB_SDQCR_FC_SHIFT ; 
 int QB_SDQCR_TOK_SHIFT ; 
 void* QB_VALID_BIT ; 
 int QMAN_REV_4100 ; 
 int QMAN_REV_MASK ; 
 int QMAN_SDQCR_TOKEN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct qbman_swp* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  qbman_read_register (struct qbman_swp*,int /*<<< orphan*/ ) ; 
 int qbman_sdqcr_dct_prio_ics ; 
 int qbman_sdqcr_fc_up_to_3 ; 
 int /*<<< orphan*/  qbman_set_swp_cfg (int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qbman_write_register (struct qbman_swp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct qbman_swp *qbman_swp_init(const struct qbman_swp_desc *d)
{
	struct qbman_swp *p = kmalloc(sizeof(*p), GFP_KERNEL);
	u32 reg;

	if (!p)
		return NULL;
	p->desc = d;
	p->mc.valid_bit = QB_VALID_BIT;
	p->sdq = 0;
	p->sdq |= qbman_sdqcr_dct_prio_ics << QB_SDQCR_DCT_SHIFT;
	p->sdq |= qbman_sdqcr_fc_up_to_3 << QB_SDQCR_FC_SHIFT;
	p->sdq |= QMAN_SDQCR_TOKEN << QB_SDQCR_TOK_SHIFT;

	atomic_set(&p->vdq.available, 1);
	p->vdq.valid_bit = QB_VALID_BIT;
	p->dqrr.next_idx = 0;
	p->dqrr.valid_bit = QB_VALID_BIT;

	if ((p->desc->qman_version & QMAN_REV_MASK) < QMAN_REV_4100) {
		p->dqrr.dqrr_size = 4;
		p->dqrr.reset_bug = 1;
	} else {
		p->dqrr.dqrr_size = 8;
		p->dqrr.reset_bug = 0;
	}

	p->addr_cena = d->cena_bar;
	p->addr_cinh = d->cinh_bar;

	reg = qbman_set_swp_cfg(p->dqrr.dqrr_size,
				1, /* Writes Non-cacheable */
				0, /* EQCR_CI stashing threshold */
				3, /* RPM: Valid bit mode, RCR in array mode */
				2, /* DCM: Discrete consumption ack mode */
				3, /* EPM: Valid bit mode, EQCR in array mode */
				0, /* mem stashing drop enable == FALSE */
				1, /* mem stashing priority == TRUE */
				0, /* mem stashing enable == FALSE */
				1, /* dequeue stashing priority == TRUE */
				0, /* dequeue stashing enable == FALSE */
				0); /* EQCR_CI stashing priority == FALSE */

	qbman_write_register(p, QBMAN_CINH_SWP_CFG, reg);
	reg = qbman_read_register(p, QBMAN_CINH_SWP_CFG);
	if (!reg) {
		pr_err("qbman: the portal is not enabled!\n");
		return NULL;
	}

	/*
	 * SDQCR needs to be initialized to 0 when no channels are
	 * being dequeued from or else the QMan HW will indicate an
	 * error.  The values that were calculated above will be
	 * applied when dequeues from a specific channel are enabled.
	 */
	qbman_write_register(p, QBMAN_CINH_SWP_SDQCR, 0);
	return p;
}