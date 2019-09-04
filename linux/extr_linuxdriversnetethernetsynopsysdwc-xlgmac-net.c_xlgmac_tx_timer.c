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
struct TYPE_2__ {int /*<<< orphan*/  napi_poll_txtimer; } ;
struct napi_struct {int dummy; } ;
struct xlgmac_pdata {TYPE_1__ stats; scalar_t__ per_channel_irq; struct napi_struct napi; } ;
struct xlgmac_channel {scalar_t__ tx_timer_active; int /*<<< orphan*/  dma_irq; struct napi_struct napi; struct xlgmac_pdata* pdata; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __napi_schedule (struct napi_struct*) ; 
 struct xlgmac_channel* channel ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 struct xlgmac_channel* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ napi_schedule_prep (struct napi_struct*) ; 
 int /*<<< orphan*/  tx_timer ; 
 int /*<<< orphan*/  xlgmac_disable_rx_tx_ints (struct xlgmac_pdata*) ; 

__attribute__((used)) static void xlgmac_tx_timer(struct timer_list *t)
{
	struct xlgmac_channel *channel = from_timer(channel, t, tx_timer);
	struct xlgmac_pdata *pdata = channel->pdata;
	struct napi_struct *napi;

	napi = (pdata->per_channel_irq) ? &channel->napi : &pdata->napi;

	if (napi_schedule_prep(napi)) {
		/* Disable Tx and Rx interrupts */
		if (pdata->per_channel_irq)
			disable_irq_nosync(channel->dma_irq);
		else
			xlgmac_disable_rx_tx_ints(pdata);

		pdata->stats.napi_poll_txtimer++;
		/* Turn on polling */
		__napi_schedule(napi);
	}

	channel->tx_timer_active = 0;
}