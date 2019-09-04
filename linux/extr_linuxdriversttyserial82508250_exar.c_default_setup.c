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
struct TYPE_2__ {int /*<<< orphan*/  regshift; scalar_t__ membase; scalar_t__ mapbase; int /*<<< orphan*/  iotype; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct pci_dev {int dummy; } ;
struct exar8250_board {int /*<<< orphan*/  reg_shift; } ;
struct exar8250 {scalar_t__ virt; struct exar8250_board* board; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPIO_MEM ; 
 scalar_t__ pci_resource_start (struct pci_dev*,unsigned int) ; 

__attribute__((used)) static int default_setup(struct exar8250 *priv, struct pci_dev *pcidev,
			 int idx, unsigned int offset,
			 struct uart_8250_port *port)
{
	const struct exar8250_board *board = priv->board;
	unsigned int bar = 0;

	port->port.iotype = UPIO_MEM;
	port->port.mapbase = pci_resource_start(pcidev, bar) + offset;
	port->port.membase = priv->virt + offset;
	port->port.regshift = board->reg_shift;

	return 0;
}