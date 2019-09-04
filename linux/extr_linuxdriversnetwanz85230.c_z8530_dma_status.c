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
typedef  int u8 ;
struct z8530_channel {int status; int dcdcheck; int* regs; scalar_t__ netdevice; TYPE_1__* dev; scalar_t__ txdma_on; int /*<<< orphan*/  txdma; scalar_t__ dma_tx; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R3 ; 
 int /*<<< orphan*/  RES_EXT_INT ; 
 int /*<<< orphan*/  RES_H_IUS ; 
 int RxENABLE ; 
 int TxEOM ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (scalar_t__) ; 
 int /*<<< orphan*/  netif_carrier_on (scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int read_zsreg (struct z8530_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  write_zsctrl (struct z8530_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_zsreg (struct z8530_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  z8530_flush_fifo (struct z8530_channel*) ; 
 int /*<<< orphan*/  z8530_tx_done (struct z8530_channel*) ; 

__attribute__((used)) static void z8530_dma_status(struct z8530_channel *chan)
{
	u8 status, altered;

	status=read_zsreg(chan, R0);
	altered=chan->status^status;
	
	chan->status=status;


	if(chan->dma_tx)
	{
		if(status&TxEOM)
		{
			unsigned long flags;
	
			flags=claim_dma_lock();
			disable_dma(chan->txdma);
			clear_dma_ff(chan->txdma);	
			chan->txdma_on=0;
			release_dma_lock(flags);
			z8530_tx_done(chan);
		}
	}

	if (altered & chan->dcdcheck)
	{
		if (status & chan->dcdcheck) {
			pr_info("%s: DCD raised\n", chan->dev->name);
			write_zsreg(chan, R3, chan->regs[3] | RxENABLE);
			if (chan->netdevice)
				netif_carrier_on(chan->netdevice);
		} else {
			pr_info("%s: DCD lost\n", chan->dev->name);
			write_zsreg(chan, R3, chan->regs[3] & ~RxENABLE);
			z8530_flush_fifo(chan);
			if (chan->netdevice)
				netif_carrier_off(chan->netdevice);
		}
	}

	write_zsctrl(chan, RES_EXT_INT);
	write_zsctrl(chan, RES_H_IUS);
}