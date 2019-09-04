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
typedef  int u32 ;
struct dwc3 {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DCTL ; 
 int DWC3_DCTL_TSTCTRL_MASK ; 
 int EINVAL ; 
#define  TEST_FORCE_EN 132 
#define  TEST_J 131 
#define  TEST_K 130 
#define  TEST_PACKET 129 
#define  TEST_SE0_NAK 128 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int dwc3_gadget_set_test_mode(struct dwc3 *dwc, int mode)
{
	u32		reg;

	reg = dwc3_readl(dwc->regs, DWC3_DCTL);
	reg &= ~DWC3_DCTL_TSTCTRL_MASK;

	switch (mode) {
	case TEST_J:
	case TEST_K:
	case TEST_SE0_NAK:
	case TEST_PACKET:
	case TEST_FORCE_EN:
		reg |= mode << 1;
		break;
	default:
		return -EINVAL;
	}

	dwc3_writel(dwc->regs, DWC3_DCTL, reg);

	return 0;
}