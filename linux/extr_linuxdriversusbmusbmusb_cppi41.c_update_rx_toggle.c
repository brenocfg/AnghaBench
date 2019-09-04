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
typedef  int u8 ;
typedef  int u16 ;
struct musb_hw_ep {int /*<<< orphan*/  regs; int /*<<< orphan*/  epnum; struct musb* musb; } ;
struct musb {int /*<<< orphan*/  mregs; } ;
struct cppi41_dma_channel {int usb_toggle; struct musb_hw_ep* hw_ep; scalar_t__ is_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_RXCSR ; 
 int MUSB_RXCSR_H_DATATOGGLE ; 
 int MUSB_RXCSR_H_WR_DATATOGGLE ; 
 int /*<<< orphan*/  is_host_active (struct musb*) ; 
 int /*<<< orphan*/  musb_dbg (struct musb*,char*) ; 
 int /*<<< orphan*/  musb_ep_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int musb_readw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void update_rx_toggle(struct cppi41_dma_channel *cppi41_channel)
{
	struct musb_hw_ep *hw_ep = cppi41_channel->hw_ep;
	struct musb *musb = hw_ep->musb;
	u16 csr;
	u8 toggle;

	if (cppi41_channel->is_tx)
		return;
	if (!is_host_active(musb))
		return;

	musb_ep_select(musb->mregs, hw_ep->epnum);
	csr = musb_readw(hw_ep->regs, MUSB_RXCSR);
	toggle = csr & MUSB_RXCSR_H_DATATOGGLE ? 1 : 0;

	/*
	 * AM335x Advisory 1.0.13: Due to internal synchronisation error the
	 * data toggle may reset from DATA1 to DATA0 during receiving data from
	 * more than one endpoint.
	 */
	if (!toggle && toggle == cppi41_channel->usb_toggle) {
		csr |= MUSB_RXCSR_H_DATATOGGLE | MUSB_RXCSR_H_WR_DATATOGGLE;
		musb_writew(cppi41_channel->hw_ep->regs, MUSB_RXCSR, csr);
		musb_dbg(musb, "Restoring DATA1 toggle.");
	}

	cppi41_channel->usb_toggle = toggle;
}