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
struct usbhs_fifo {int /*<<< orphan*/  sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbhs_pipe_select_fifo (struct usbhs_pipe*,int /*<<< orphan*/ *) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_write (struct usbhs_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbhsf_fifo_unselect(struct usbhs_pipe *pipe,
				 struct usbhs_fifo *fifo)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);

	usbhs_pipe_select_fifo(pipe, NULL);
	usbhs_write(priv, fifo->sel, 0);
}