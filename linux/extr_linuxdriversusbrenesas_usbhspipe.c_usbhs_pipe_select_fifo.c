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
struct usbhs_pipe {struct usbhs_fifo* fifo; } ;
struct usbhs_fifo {struct usbhs_pipe* pipe; } ;

/* Variables and functions */

void usbhs_pipe_select_fifo(struct usbhs_pipe *pipe, struct usbhs_fifo *fifo)
{
	if (pipe->fifo)
		pipe->fifo->pipe = NULL;

	pipe->fifo = fifo;

	if (fifo)
		fifo->pipe = pipe;
}