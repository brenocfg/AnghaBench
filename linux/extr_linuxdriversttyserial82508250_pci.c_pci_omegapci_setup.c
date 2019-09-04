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
struct uart_8250_port {int dummy; } ;
struct serial_private {int dummy; } ;
struct pciserial_board {int dummy; } ;

/* Variables and functions */
 int setup_port (struct serial_private*,struct uart_8250_port*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_omegapci_setup(struct serial_private *priv,
		      const struct pciserial_board *board,
		      struct uart_8250_port *port, int idx)
{
	return setup_port(priv, port, 2, idx * 8, 0);
}