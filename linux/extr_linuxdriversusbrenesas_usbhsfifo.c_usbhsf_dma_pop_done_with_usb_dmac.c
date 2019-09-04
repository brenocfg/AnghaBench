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
struct usbhs_priv {int dummy; } ;
struct usbhs_pkt {int /*<<< orphan*/  actual; struct usbhs_pipe* pipe; } ;
struct usbhs_pipe {int /*<<< orphan*/  fifo; } ;
struct usbhs_fifo {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRDYSTS ; 
 int /*<<< orphan*/  usbhs_dma_calc_received_size (struct usbhs_pkt*,struct dma_chan*,int) ; 
 int /*<<< orphan*/  usbhs_pipe_number (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_running (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 struct usbhs_fifo* usbhs_pipe_to_fifo (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_xxxsts_clear (struct usbhs_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dma_chan* usbhsf_dma_chan_get (struct usbhs_fifo*,struct usbhs_pkt*) ; 
 int /*<<< orphan*/  usbhsf_dma_stop (struct usbhs_pipe*,struct usbhs_fifo*) ; 
 int /*<<< orphan*/  usbhsf_dma_unmap (struct usbhs_pkt*) ; 
 int /*<<< orphan*/  usbhsf_fifo_clear (struct usbhs_pipe*,struct usbhs_fifo*) ; 
 int usbhsf_fifo_rcv_len (struct usbhs_priv*,struct usbhs_fifo*) ; 
 int /*<<< orphan*/  usbhsf_fifo_unselect (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhsf_dma_pop_done_with_usb_dmac(struct usbhs_pkt *pkt,
					     int *is_done)
{
	struct usbhs_pipe *pipe = pkt->pipe;
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct usbhs_fifo *fifo = usbhs_pipe_to_fifo(pipe);
	struct dma_chan *chan = usbhsf_dma_chan_get(fifo, pkt);
	int rcv_len;

	/*
	 * Since the driver disables rx_irq in DMA mode, the interrupt handler
	 * cannot the BRDYSTS. So, the function clears it here because the
	 * driver may use PIO mode next time.
	 */
	usbhs_xxxsts_clear(priv, BRDYSTS, usbhs_pipe_number(pipe));

	rcv_len = usbhsf_fifo_rcv_len(priv, fifo);
	usbhsf_fifo_clear(pipe, fifo);
	pkt->actual = usbhs_dma_calc_received_size(pkt, chan, rcv_len);

	usbhs_pipe_running(pipe, 0);
	usbhsf_dma_stop(pipe, fifo);
	usbhsf_dma_unmap(pkt);
	usbhsf_fifo_unselect(pipe, pipe->fifo);

	/* The driver can assume the rx transaction is always "done" */
	*is_done = 1;

	return 0;
}