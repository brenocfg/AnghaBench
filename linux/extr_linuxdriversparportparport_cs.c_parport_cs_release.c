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
struct pcmcia_device {int /*<<< orphan*/  dev; TYPE_1__* priv; } ;
struct parport {int dummy; } ;
struct TYPE_2__ {scalar_t__ ndev; struct parport* port; } ;
typedef  TYPE_1__ parport_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  parport_pc_unregister_port (struct parport*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void parport_cs_release(struct pcmcia_device *link)
{
	parport_info_t *info = link->priv;

	dev_dbg(&link->dev, "parport_release\n");

	if (info->ndev) {
		struct parport *p = info->port;
		parport_pc_unregister_port(p);
	}
	info->ndev = 0;

	pcmcia_disable_device(link);
}