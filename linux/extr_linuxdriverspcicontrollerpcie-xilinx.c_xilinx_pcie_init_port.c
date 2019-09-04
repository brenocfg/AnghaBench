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
struct xilinx_pcie_port {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int XILINX_PCIE_IDR_ALL_MASK ; 
 int XILINX_PCIE_IMR_ALL_MASK ; 
 int XILINX_PCIE_IMR_ENABLE_MASK ; 
 int /*<<< orphan*/  XILINX_PCIE_REG_IDR ; 
 int /*<<< orphan*/  XILINX_PCIE_REG_IMR ; 
 int /*<<< orphan*/  XILINX_PCIE_REG_RPSC ; 
 int XILINX_PCIE_REG_RPSC_BEN ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int pcie_read (struct xilinx_pcie_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_write (struct xilinx_pcie_port*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xilinx_pcie_link_up (struct xilinx_pcie_port*) ; 

__attribute__((used)) static void xilinx_pcie_init_port(struct xilinx_pcie_port *port)
{
	struct device *dev = port->dev;

	if (xilinx_pcie_link_up(port))
		dev_info(dev, "PCIe Link is UP\n");
	else
		dev_info(dev, "PCIe Link is DOWN\n");

	/* Disable all interrupts */
	pcie_write(port, ~XILINX_PCIE_IDR_ALL_MASK,
		   XILINX_PCIE_REG_IMR);

	/* Clear pending interrupts */
	pcie_write(port, pcie_read(port, XILINX_PCIE_REG_IDR) &
			 XILINX_PCIE_IMR_ALL_MASK,
		   XILINX_PCIE_REG_IDR);

	/* Enable all interrupts we handle */
	pcie_write(port, XILINX_PCIE_IMR_ENABLE_MASK, XILINX_PCIE_REG_IMR);

	/* Enable the Bridge enable bit */
	pcie_write(port, pcie_read(port, XILINX_PCIE_REG_RPSC) |
			 XILINX_PCIE_REG_RPSC_BEN,
		   XILINX_PCIE_REG_RPSC);
}