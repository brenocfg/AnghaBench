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
typedef  int u16 ;
struct yenta_socket {struct pci_dev* dev; } ;
struct pci_dev {TYPE_2__* subordinate; int /*<<< orphan*/ * resource; int /*<<< orphan*/  bus; } ;
struct pci_bus_region {int start; } ;
struct TYPE_3__ {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_4__ {int primary; TYPE_1__ busn_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB_BRIDGE_CONTROL ; 
 int CB_BRIDGE_CRST ; 
 int CB_BRIDGE_ISAEN ; 
 int CB_BRIDGE_POSTEN ; 
 int CB_BRIDGE_PREFETCH0 ; 
 int CB_BRIDGE_PREFETCH1 ; 
 int CB_BRIDGE_VGAEN ; 
 int /*<<< orphan*/  CB_LEGACY_MODE_BASE ; 
 int L1_CACHE_BYTES ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_0 ; 
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
 int PCI_COMMAND_WAIT ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int /*<<< orphan*/  PCI_PRIMARY_BUS ; 
 int config_readw (struct yenta_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_writeb (struct yenta_socket*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  config_writel (struct yenta_socket*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  config_writew (struct yenta_socket*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcibios_resource_to_bus (int /*<<< orphan*/ ,struct pci_bus_region*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void yenta_config_init(struct yenta_socket *socket)
{
	u16 bridge;
	struct pci_dev *dev = socket->dev;
	struct pci_bus_region region;

	pcibios_resource_to_bus(socket->dev->bus, &region, &dev->resource[0]);

	config_writel(socket, CB_LEGACY_MODE_BASE, 0);
	config_writel(socket, PCI_BASE_ADDRESS_0, region.start);
	config_writew(socket, PCI_COMMAND,
			PCI_COMMAND_IO |
			PCI_COMMAND_MEMORY |
			PCI_COMMAND_MASTER |
			PCI_COMMAND_WAIT);

	/* MAGIC NUMBERS! Fixme */
	config_writeb(socket, PCI_CACHE_LINE_SIZE, L1_CACHE_BYTES / 4);
	config_writeb(socket, PCI_LATENCY_TIMER, 168);
	config_writel(socket, PCI_PRIMARY_BUS,
		(176 << 24) |			   /* sec. latency timer */
		((unsigned int)dev->subordinate->busn_res.end << 16) | /* subordinate bus */
		((unsigned int)dev->subordinate->busn_res.start << 8) |  /* secondary bus */
		dev->subordinate->primary);		   /* primary bus */

	/*
	 * Set up the bridging state:
	 *  - enable write posting.
	 *  - memory window 0 prefetchable, window 1 non-prefetchable
	 *  - PCI interrupts enabled if a PCI interrupt exists..
	 */
	bridge = config_readw(socket, CB_BRIDGE_CONTROL);
	bridge &= ~(CB_BRIDGE_CRST | CB_BRIDGE_PREFETCH1 | CB_BRIDGE_ISAEN | CB_BRIDGE_VGAEN);
	bridge |= CB_BRIDGE_PREFETCH0 | CB_BRIDGE_POSTEN;
	config_writew(socket, CB_BRIDGE_CONTROL, bridge);
}