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
struct xhci_hcd {struct xhci_dbc* dbc; } ;
struct dbc_port {int registered; int /*<<< orphan*/  write_pool; int /*<<< orphan*/  read_queue; int /*<<< orphan*/  read_pool; int /*<<< orphan*/  write_fifo; } ;
struct xhci_dbc {struct dbc_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbc_tty_driver ; 
 int /*<<< orphan*/  get_in_ep (struct xhci_hcd*) ; 
 int /*<<< orphan*/  get_out_ep (struct xhci_hcd*) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbc_free_requests (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_dbc_tty_exit_port (struct dbc_port*) ; 

void xhci_dbc_tty_unregister_device(struct xhci_hcd *xhci)
{
	struct xhci_dbc		*dbc = xhci->dbc;
	struct dbc_port		*port = &dbc->port;

	tty_unregister_device(dbc_tty_driver, 0);
	xhci_dbc_tty_exit_port(port);
	port->registered = false;

	kfifo_free(&port->write_fifo);
	xhci_dbc_free_requests(get_out_ep(xhci), &port->read_pool);
	xhci_dbc_free_requests(get_out_ep(xhci), &port->read_queue);
	xhci_dbc_free_requests(get_in_ep(xhci), &port->write_pool);
}