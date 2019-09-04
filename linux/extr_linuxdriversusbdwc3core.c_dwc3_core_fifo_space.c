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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct dwc3_ep {int /*<<< orphan*/  number; struct dwc3* dwc; } ;
struct dwc3 {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GDBGFIFOSPACE ; 
 int DWC3_GDBGFIFOSPACE_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_GDBGFIFOSPACE_SPACE_AVAILABLE (int /*<<< orphan*/ ) ; 
 int DWC3_GDBGFIFOSPACE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

u32 dwc3_core_fifo_space(struct dwc3_ep *dep, u8 type)
{
	struct dwc3		*dwc = dep->dwc;
	u32			reg;

	dwc3_writel(dwc->regs, DWC3_GDBGFIFOSPACE,
			DWC3_GDBGFIFOSPACE_NUM(dep->number) |
			DWC3_GDBGFIFOSPACE_TYPE(type));

	reg = dwc3_readl(dwc->regs, DWC3_GDBGFIFOSPACE);

	return DWC3_GDBGFIFOSPACE_SPACE_AVAILABLE(reg);
}