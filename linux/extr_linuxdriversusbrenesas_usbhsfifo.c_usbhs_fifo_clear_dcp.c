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
struct usbhs_pipe {int dummy; } ;
struct usbhs_fifo {int dummy; } ;

/* Variables and functions */
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhsf_fifo_clear (struct usbhs_pipe*,struct usbhs_fifo*) ; 
 scalar_t__ usbhsf_fifo_select (struct usbhs_pipe*,struct usbhs_fifo*,int) ; 
 int /*<<< orphan*/  usbhsf_fifo_unselect (struct usbhs_pipe*,struct usbhs_fifo*) ; 
 struct usbhs_fifo* usbhsf_get_cfifo (struct usbhs_priv*) ; 

void usbhs_fifo_clear_dcp(struct usbhs_pipe *pipe)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct usbhs_fifo *fifo = usbhsf_get_cfifo(priv); /* CFIFO */

	/* clear DCP FIFO of transmission */
	if (usbhsf_fifo_select(pipe, fifo, 1) < 0)
		return;
	usbhsf_fifo_clear(pipe, fifo);
	usbhsf_fifo_unselect(pipe, fifo);

	/* clear DCP FIFO of reception */
	if (usbhsf_fifo_select(pipe, fifo, 0) < 0)
		return;
	usbhsf_fifo_clear(pipe, fifo);
	usbhsf_fifo_unselect(pipe, fifo);
}