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
typedef  int u32 ;
struct mtk_eth {int /*<<< orphan*/  rx_napi; TYPE_1__* soc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int rx_int; int tx_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mtk_irq_ack (struct mtk_eth*,int) ; 
 int /*<<< orphan*/  mtk_irq_disable (struct mtk_eth*,int) ; 
 int mtk_irq_pending (struct mtk_eth*) ; 
 int napi_schedule_prep (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t mtk_handle_irq(int irq, void *_eth)
{
	struct mtk_eth *eth = _eth;
	u32 status, int_mask;

	status = mtk_irq_pending(eth);
	if (unlikely(!status))
		return IRQ_NONE;

	int_mask = (eth->soc->rx_int | eth->soc->tx_int);
	if (likely(status & int_mask)) {
		if (likely(napi_schedule_prep(&eth->rx_napi)))
			__napi_schedule(&eth->rx_napi);
	} else {
		mtk_irq_ack(eth, status);
	}
	mtk_irq_disable(eth, int_mask);

	return IRQ_HANDLED;
}