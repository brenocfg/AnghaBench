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
struct usbhs_pkt {int /*<<< orphan*/ * handler; } ;
struct usbhs_fifo {struct dma_chan* rx_chan; struct dma_chan* tx_chan; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbhs_fifo_dma_pop_handler ; 
 int /*<<< orphan*/  usbhs_fifo_dma_push_handler ; 

__attribute__((used)) static struct dma_chan *usbhsf_dma_chan_get(struct usbhs_fifo *fifo,
					    struct usbhs_pkt *pkt)
{
	if (&usbhs_fifo_dma_push_handler == pkt->handler)
		return fifo->tx_chan;

	if (&usbhs_fifo_dma_pop_handler == pkt->handler)
		return fifo->rx_chan;

	return NULL;
}