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
struct tegra_pcie_port {int index; } ;

/* Variables and functions */
 unsigned long AFI_PEX0_CTRL ; 
 unsigned long AFI_PEX1_CTRL ; 
 unsigned long AFI_PEX2_CTRL ; 

__attribute__((used)) static unsigned long tegra_pcie_port_get_pex_ctrl(struct tegra_pcie_port *port)
{
	unsigned long ret = 0;

	switch (port->index) {
	case 0:
		ret = AFI_PEX0_CTRL;
		break;

	case 1:
		ret = AFI_PEX1_CTRL;
		break;

	case 2:
		ret = AFI_PEX2_CTRL;
		break;
	}

	return ret;
}