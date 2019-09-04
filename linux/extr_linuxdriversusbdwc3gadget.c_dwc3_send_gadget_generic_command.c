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
typedef  unsigned int u32 ;
struct dwc3 {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DGCMD ; 
 int /*<<< orphan*/  DWC3_DGCMDPAR ; 
 unsigned int DWC3_DGCMD_CMDACT ; 
 int DWC3_DGCMD_STATUS (unsigned int) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 unsigned int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  trace_dwc3_gadget_generic_cmd (unsigned int,unsigned int,int) ; 

int dwc3_send_gadget_generic_command(struct dwc3 *dwc, unsigned cmd, u32 param)
{
	u32		timeout = 500;
	int		status = 0;
	int		ret = 0;
	u32		reg;

	dwc3_writel(dwc->regs, DWC3_DGCMDPAR, param);
	dwc3_writel(dwc->regs, DWC3_DGCMD, cmd | DWC3_DGCMD_CMDACT);

	do {
		reg = dwc3_readl(dwc->regs, DWC3_DGCMD);
		if (!(reg & DWC3_DGCMD_CMDACT)) {
			status = DWC3_DGCMD_STATUS(reg);
			if (status)
				ret = -EINVAL;
			break;
		}
	} while (--timeout);

	if (!timeout) {
		ret = -ETIMEDOUT;
		status = -ETIMEDOUT;
	}

	trace_dwc3_gadget_generic_cmd(cmd, param, status);

	return ret;
}