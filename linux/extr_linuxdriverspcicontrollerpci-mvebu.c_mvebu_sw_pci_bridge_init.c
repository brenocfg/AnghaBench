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
struct mvebu_sw_pci_bridge {int device; int revision; int cache_line_size; int /*<<< orphan*/  status; void* iolimit; void* iobase; int /*<<< orphan*/  header_type; int /*<<< orphan*/  vendor; int /*<<< orphan*/  class; } ;
struct mvebu_pcie_port {struct mvebu_sw_pci_bridge bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_DEV_ID_OFF ; 
 int /*<<< orphan*/  PCIE_DEV_REV_OFF ; 
 int /*<<< orphan*/  PCI_CLASS_BRIDGE_PCI ; 
 int /*<<< orphan*/  PCI_HEADER_TYPE_BRIDGE ; 
 void* PCI_IO_RANGE_TYPE_32 ; 
 int /*<<< orphan*/  PCI_STATUS_CAP_LIST ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_MARVELL ; 
 int /*<<< orphan*/  memset (struct mvebu_sw_pci_bridge*,int /*<<< orphan*/ ,int) ; 
 int mvebu_readl (struct mvebu_pcie_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvebu_sw_pci_bridge_init(struct mvebu_pcie_port *port)
{
	struct mvebu_sw_pci_bridge *bridge = &port->bridge;

	memset(bridge, 0, sizeof(struct mvebu_sw_pci_bridge));

	bridge->class = PCI_CLASS_BRIDGE_PCI;
	bridge->vendor = PCI_VENDOR_ID_MARVELL;
	bridge->device = mvebu_readl(port, PCIE_DEV_ID_OFF) >> 16;
	bridge->revision = mvebu_readl(port, PCIE_DEV_REV_OFF) & 0xff;
	bridge->header_type = PCI_HEADER_TYPE_BRIDGE;
	bridge->cache_line_size = 0x10;

	/* We support 32 bits I/O addressing */
	bridge->iobase = PCI_IO_RANGE_TYPE_32;
	bridge->iolimit = PCI_IO_RANGE_TYPE_32;

	/* Add capabilities */
	bridge->status = PCI_STATUS_CAP_LIST;
}