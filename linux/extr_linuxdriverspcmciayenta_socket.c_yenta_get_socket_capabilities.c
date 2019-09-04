#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ irq_mask; int /*<<< orphan*/  pci_irq; } ;
struct yenta_socket {int /*<<< orphan*/  cb_irq; TYPE_1__ socket; TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ isa_probe ; 
 scalar_t__ yenta_probe_irq (struct yenta_socket*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yenta_get_socket_capabilities(struct yenta_socket *socket, u32 isa_irq_mask)
{
	socket->socket.pci_irq = socket->cb_irq;
	if (isa_probe)
		socket->socket.irq_mask = yenta_probe_irq(socket, isa_irq_mask);
	else
		socket->socket.irq_mask = 0;

	dev_info(&socket->dev->dev, "ISA IRQ mask 0x%04x, PCI irq %d\n",
		 socket->socket.irq_mask, socket->cb_irq);
}