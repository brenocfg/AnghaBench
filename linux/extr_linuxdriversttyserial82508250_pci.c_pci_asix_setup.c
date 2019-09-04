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
struct uart_8250_port {int /*<<< orphan*/  bugs; } ;
struct serial_private {int dummy; } ;
struct pciserial_board {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_BUG_PARITY ; 
 int pci_default_setup (struct serial_private*,struct pciserial_board const*,struct uart_8250_port*,int) ; 

__attribute__((used)) static int pci_asix_setup(struct serial_private *priv,
		  const struct pciserial_board *board,
		  struct uart_8250_port *port, int idx)
{
	port->bugs |= UART_BUG_PARITY;
	return pci_default_setup(priv, board, port, idx);
}