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
struct dwc3_event_buffer {scalar_t__ lpos; } ;
struct dwc3 {int /*<<< orphan*/  regs; struct dwc3_event_buffer* ev_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GEVNTADRHI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_GEVNTADRLO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_GEVNTCOUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_GEVNTSIZ (int /*<<< orphan*/ ) ; 
 int DWC3_GEVNTSIZ_INTMASK ; 
 int DWC3_GEVNTSIZ_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void dwc3_event_buffers_cleanup(struct dwc3 *dwc)
{
	struct dwc3_event_buffer	*evt;

	evt = dwc->ev_buf;

	evt->lpos = 0;

	dwc3_writel(dwc->regs, DWC3_GEVNTADRLO(0), 0);
	dwc3_writel(dwc->regs, DWC3_GEVNTADRHI(0), 0);
	dwc3_writel(dwc->regs, DWC3_GEVNTSIZ(0), DWC3_GEVNTSIZ_INTMASK
			| DWC3_GEVNTSIZ_SIZE(0));
	dwc3_writel(dwc->regs, DWC3_GEVNTCOUNT(0), 0);
}