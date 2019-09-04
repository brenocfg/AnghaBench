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
struct TYPE_3__ {scalar_t__ frame_gap; int /*<<< orphan*/  control; } ;
struct TYPE_4__ {TYPE_1__ wregs; } ;
struct sgiseeq_regs {int /*<<< orphan*/  tstat; TYPE_2__ rw; } ;
struct sgiseeq_private {int /*<<< orphan*/  tx_desc; int /*<<< orphan*/  rx_desc; int /*<<< orphan*/  control; scalar_t__ is_edlc; struct hpc3_ethregs* hregs; } ;
struct net_device {int dummy; } ;
struct hpc3_ethregs {void* tx_ndptr; void* rx_ndptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSTAT_INIT_EDLC ; 
 int /*<<< orphan*/  TSTAT_INIT_SEEQ ; 
 void* VIRT_TO_DMA (struct sgiseeq_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_hpc3_and_seeq (struct hpc3_ethregs*,struct sgiseeq_regs*) ; 
 int /*<<< orphan*/  seeq_go (struct sgiseeq_private*,struct hpc3_ethregs*,struct sgiseeq_regs*) ; 
 int seeq_init_ring (struct net_device*) ; 

__attribute__((used)) static int init_seeq(struct net_device *dev, struct sgiseeq_private *sp,
		     struct sgiseeq_regs *sregs)
{
	struct hpc3_ethregs *hregs = sp->hregs;
	int err;

	reset_hpc3_and_seeq(hregs, sregs);
	err = seeq_init_ring(dev);
	if (err)
		return err;

	/* Setup to field the proper interrupt types. */
	if (sp->is_edlc) {
		sregs->tstat = TSTAT_INIT_EDLC;
		sregs->rw.wregs.control = sp->control;
		sregs->rw.wregs.frame_gap = 0;
	} else {
		sregs->tstat = TSTAT_INIT_SEEQ;
	}

	hregs->rx_ndptr = VIRT_TO_DMA(sp, sp->rx_desc);
	hregs->tx_ndptr = VIRT_TO_DMA(sp, sp->tx_desc);

	seeq_go(sp, hregs, sregs);
	return 0;
}