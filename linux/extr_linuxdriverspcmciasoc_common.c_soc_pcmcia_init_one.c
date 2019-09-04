#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  pci_irq; TYPE_1__ dev; int /*<<< orphan*/  owner; } ;
struct soc_pcmcia_socket {TYPE_3__* stat; TYPE_2__ socket; struct pcmcia_low_level const* ops; } ;
struct pcmcia_low_level {int /*<<< orphan*/  owner; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  NO_IRQ ; 

void soc_pcmcia_init_one(struct soc_pcmcia_socket *skt,
	const struct pcmcia_low_level *ops, struct device *dev)
{
	int i;

	skt->ops = ops;
	skt->socket.owner = ops->owner;
	skt->socket.dev.parent = dev;
	skt->socket.pci_irq = NO_IRQ;

	for (i = 0; i < ARRAY_SIZE(skt->stat); i++)
		skt->stat[i].gpio = -EINVAL;
}