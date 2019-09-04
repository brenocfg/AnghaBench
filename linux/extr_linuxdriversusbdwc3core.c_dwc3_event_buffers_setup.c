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
struct dwc3_event_buffer {int /*<<< orphan*/  length; int /*<<< orphan*/  dma; scalar_t__ lpos; } ;
struct dwc3 {int /*<<< orphan*/  regs; struct dwc3_event_buffer* ev_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GEVNTADRHI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_GEVNTADRLO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_GEVNTCOUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_GEVNTSIZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_GEVNTSIZ_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

int dwc3_event_buffers_setup(struct dwc3 *dwc)
{
	struct dwc3_event_buffer	*evt;

	evt = dwc->ev_buf;
	evt->lpos = 0;
	dwc3_writel(dwc->regs, DWC3_GEVNTADRLO(0),
			lower_32_bits(evt->dma));
	dwc3_writel(dwc->regs, DWC3_GEVNTADRHI(0),
			upper_32_bits(evt->dma));
	dwc3_writel(dwc->regs, DWC3_GEVNTSIZ(0),
			DWC3_GEVNTSIZ_SIZE(evt->length));
	dwc3_writel(dwc->regs, DWC3_GEVNTCOUNT(0), 0);

	return 0;
}