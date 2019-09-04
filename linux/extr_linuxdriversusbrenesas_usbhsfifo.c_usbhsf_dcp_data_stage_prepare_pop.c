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
struct usbhs_priv {int dummy; } ;
struct usbhs_pkt {TYPE_1__* handler; struct usbhs_pipe* pipe; } ;
struct usbhs_pipe {int dummy; } ;
struct usbhs_fifo {int dummy; } ;
struct TYPE_2__ {int (* prepare ) (struct usbhs_pkt*,int*) ;} ;

/* Variables and functions */
 int stub1 (struct usbhs_pkt*,int*) ; 
 TYPE_1__ usbhs_fifo_pio_pop_handler ; 
 int /*<<< orphan*/  usbhs_pipe_disable (struct usbhs_pipe*) ; 
 scalar_t__ usbhs_pipe_is_busy (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_sequence_data1 (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhsf_fifo_clear (struct usbhs_pipe*,struct usbhs_fifo*) ; 
 int /*<<< orphan*/  usbhsf_fifo_select (struct usbhs_pipe*,struct usbhs_fifo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsf_fifo_unselect (struct usbhs_pipe*,struct usbhs_fifo*) ; 
 struct usbhs_fifo* usbhsf_get_cfifo (struct usbhs_priv*) ; 

__attribute__((used)) static int usbhsf_dcp_data_stage_prepare_pop(struct usbhs_pkt *pkt,
					     int *is_done)
{
	struct usbhs_pipe *pipe = pkt->pipe;
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct usbhs_fifo *fifo = usbhsf_get_cfifo(priv);

	if (usbhs_pipe_is_busy(pipe))
		return 0;

	/*
	 * prepare pop for DCP should
	 *  - change DCP direction,
	 *  - clear fifo
	 *  - DATA1
	 */
	usbhs_pipe_disable(pipe);

	usbhs_pipe_sequence_data1(pipe); /* DATA1 */

	usbhsf_fifo_select(pipe, fifo, 0);
	usbhsf_fifo_clear(pipe, fifo);
	usbhsf_fifo_unselect(pipe, fifo);

	/*
	 * change handler to PIO pop
	 */
	pkt->handler = &usbhs_fifo_pio_pop_handler;

	return pkt->handler->prepare(pkt, is_done);
}