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
struct uart_8250_port {int dummy; } ;
struct serial_private {TYPE_1__* dev; } ;
struct pciserial_board {unsigned int first_offset; int uart_offset; int /*<<< orphan*/  reg_shift; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int subsystem_device; } ;

/* Variables and functions */
 unsigned int FL_GET_BASE (int /*<<< orphan*/ ) ; 
#define  PCI_DEVICE_ID_HP_DIVA_EVEREST 129 
#define  PCI_DEVICE_ID_HP_DIVA_MAESTRO 128 
 int setup_port (struct serial_private*,struct uart_8250_port*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_hp_diva_setup(struct serial_private *priv,
		const struct pciserial_board *board,
		struct uart_8250_port *port, int idx)
{
	unsigned int offset = board->first_offset;
	unsigned int bar = FL_GET_BASE(board->flags);

	switch (priv->dev->subsystem_device) {
	case PCI_DEVICE_ID_HP_DIVA_MAESTRO:
		if (idx == 3)
			idx++;
		break;
	case PCI_DEVICE_ID_HP_DIVA_EVEREST:
		if (idx > 0)
			idx++;
		if (idx > 2)
			idx++;
		break;
	}
	if (idx > 2)
		offset = 0x18;

	offset += idx * board->uart_offset;

	return setup_port(priv, port, bar, offset, board->reg_shift);
}