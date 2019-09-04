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
typedef  size_t u32 ;
struct stmmac_priv {int /*<<< orphan*/  ioaddr; struct stmmac_channel* channel; int /*<<< orphan*/  xstats; } ;
struct stmmac_channel {int /*<<< orphan*/  napi; scalar_t__ has_tx; scalar_t__ has_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int handle_rx ; 
 int handle_tx ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_disable_dma_irq (struct stmmac_priv*,int /*<<< orphan*/ ,size_t) ; 
 int stmmac_dma_interrupt_status (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int stmmac_napi_check(struct stmmac_priv *priv, u32 chan)
{
	int status = stmmac_dma_interrupt_status(priv, priv->ioaddr,
						 &priv->xstats, chan);
	struct stmmac_channel *ch = &priv->channel[chan];
	bool needs_work = false;

	if ((status & handle_rx) && ch->has_rx) {
		needs_work = true;
	} else {
		status &= ~handle_rx;
	}

	if ((status & handle_tx) && ch->has_tx) {
		needs_work = true;
	} else {
		status &= ~handle_tx;
	}

	if (needs_work && napi_schedule_prep(&ch->napi)) {
		stmmac_disable_dma_irq(priv, priv->ioaddr, chan);
		__napi_schedule(&ch->napi);
	}

	return status;
}