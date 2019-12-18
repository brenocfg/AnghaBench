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
struct sata_oxnas_host_priv {int n_ports; } ;
struct TYPE_5__ {TYPE_3__* device; } ;
struct ata_port {TYPE_2__ link; TYPE_1__* host; } ;
struct ata_link {struct ata_port* ap; } ;
struct TYPE_6__ {scalar_t__ class; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ports; struct sata_oxnas_host_priv* private_data; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 unsigned int ATA_DEV_NONE ; 
 unsigned int ATA_MAX_DEVICES ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  ata_std_postreset (struct ata_link*,unsigned int*) ; 
 int /*<<< orphan*/  sata_oxnas_dev_config (TYPE_3__*) ; 
 int /*<<< orphan*/  sata_oxnas_link_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void sata_oxnas_postreset(struct ata_link *link, unsigned int *classes)
{
	struct ata_port *ap = link->ap;
	struct sata_oxnas_host_priv *hd = ap->host->private_data;

	unsigned int dev;

	DPRINTK("ENTER\n");
	ata_std_postreset(link, classes);

	/* turn on phy error detection by removing the masks */
	sata_oxnas_link_write(ap->host->ports[0], 0x0c, 0x30003);
	if (hd->n_ports > 1)
		sata_oxnas_link_write(ap->host->ports[1], 0x0c, 0x30003);

	/* bail out if no device is present */
	if (classes[0] == ATA_DEV_NONE && classes[1] == ATA_DEV_NONE) {
		DPRINTK("EXIT, no device\n");
		return;
	}

	/* go through all the devices and configure them */
	for (dev = 0; dev < ATA_MAX_DEVICES; ++dev) {
		if (ap->link.device[dev].class == ATA_DEV_ATA)
			sata_oxnas_dev_config(&(ap->link.device[dev]));
	}

	DPRINTK("EXIT\n");
}