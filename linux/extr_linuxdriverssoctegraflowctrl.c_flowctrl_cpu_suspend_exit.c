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

/* Variables and functions */
 unsigned int FLOW_CTRL_CSR_ENABLE ; 
 unsigned int FLOW_CTRL_CSR_EVENT_FLAG ; 
 unsigned int FLOW_CTRL_CSR_INTR_FLAG ; 
#define  TEGRA114 131 
#define  TEGRA124 130 
#define  TEGRA20 129 
 unsigned int TEGRA20_FLOW_CTRL_CSR_WFE_BITMAP ; 
 unsigned int TEGRA20_FLOW_CTRL_CSR_WFI_BITMAP ; 
#define  TEGRA30 128 
 unsigned int TEGRA30_FLOW_CTRL_CSR_WFE_BITMAP ; 
 unsigned int TEGRA30_FLOW_CTRL_CSR_WFI_BITMAP ; 
 unsigned int flowctrl_read_cpu_csr (unsigned int) ; 
 int /*<<< orphan*/  flowctrl_write_cpu_csr (unsigned int,unsigned int) ; 
 int tegra_get_chip_id () ; 

void flowctrl_cpu_suspend_exit(unsigned int cpuid)
{
	unsigned int reg;

	/* Disable powergating via flow controller for CPU0 */
	reg = flowctrl_read_cpu_csr(cpuid);
	switch (tegra_get_chip_id()) {
	case TEGRA20:
		/* clear wfe bitmap */
		reg &= ~TEGRA20_FLOW_CTRL_CSR_WFE_BITMAP;
		/* clear wfi bitmap */
		reg &= ~TEGRA20_FLOW_CTRL_CSR_WFI_BITMAP;
		break;
	case TEGRA30:
	case TEGRA114:
	case TEGRA124:
		/* clear wfe bitmap */
		reg &= ~TEGRA30_FLOW_CTRL_CSR_WFE_BITMAP;
		/* clear wfi bitmap */
		reg &= ~TEGRA30_FLOW_CTRL_CSR_WFI_BITMAP;
		break;
	}
	reg &= ~FLOW_CTRL_CSR_ENABLE;			/* clear enable */
	reg |= FLOW_CTRL_CSR_INTR_FLAG;			/* clear intr */
	reg |= FLOW_CTRL_CSR_EVENT_FLAG;		/* clear event */
	flowctrl_write_cpu_csr(cpuid, reg);
}