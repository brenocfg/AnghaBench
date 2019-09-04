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
typedef  int u8 ;
typedef  int u16 ;
struct cppi41_dma_channel {int usb_toggle; TYPE_3__* hw_ep; TYPE_2__* controller; scalar_t__ is_tx; } ;
struct TYPE_6__ {int /*<<< orphan*/  regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  musb; } ;
struct TYPE_5__ {TYPE_1__ controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_RXCSR ; 
 int MUSB_RXCSR_H_DATATOGGLE ; 
 int /*<<< orphan*/  is_host_active (int /*<<< orphan*/ ) ; 
 int musb_readw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void save_rx_toggle(struct cppi41_dma_channel *cppi41_channel)
{
	u16 csr;
	u8 toggle;

	if (cppi41_channel->is_tx)
		return;
	if (!is_host_active(cppi41_channel->controller->controller.musb))
		return;

	csr = musb_readw(cppi41_channel->hw_ep->regs, MUSB_RXCSR);
	toggle = csr & MUSB_RXCSR_H_DATATOGGLE ? 1 : 0;

	cppi41_channel->usb_toggle = toggle;
}