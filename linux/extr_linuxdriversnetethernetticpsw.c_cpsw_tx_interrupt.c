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
struct cpsw_common {int tx_irq_disabled; int /*<<< orphan*/  napi_tx; int /*<<< orphan*/ * irqs_table; scalar_t__ quirk_irq; int /*<<< orphan*/  dma; TYPE_1__* wr_regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  tx_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPDMA_EOI_TX ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cpdma_ctlr_eoi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cpsw_tx_interrupt(int irq, void *dev_id)
{
	struct cpsw_common *cpsw = dev_id;

	writel(0, &cpsw->wr_regs->tx_en);
	cpdma_ctlr_eoi(cpsw->dma, CPDMA_EOI_TX);

	if (cpsw->quirk_irq) {
		disable_irq_nosync(cpsw->irqs_table[1]);
		cpsw->tx_irq_disabled = true;
	}

	napi_schedule(&cpsw->napi_tx);
	return IRQ_HANDLED;
}