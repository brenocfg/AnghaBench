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
union dwc3_event {int raw; } ;
typedef  int u32 ;
struct dwc3_event_buffer {int count; int flags; int lpos; int length; scalar_t__ cache; struct dwc3* dwc; } ;
struct dwc3 {int imod_interval; int /*<<< orphan*/  regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DEV_IMOD (int /*<<< orphan*/ ) ; 
 int DWC3_EVENT_PENDING ; 
 int /*<<< orphan*/  DWC3_GEVNTCOUNT (int /*<<< orphan*/ ) ; 
 int DWC3_GEVNTCOUNT_EHB ; 
 int /*<<< orphan*/  DWC3_GEVNTSIZ (int /*<<< orphan*/ ) ; 
 int DWC3_GEVNTSIZ_INTMASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dwc3_process_event_entry (struct dwc3*,union dwc3_event*) ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t dwc3_process_event_buf(struct dwc3_event_buffer *evt)
{
	struct dwc3 *dwc = evt->dwc;
	irqreturn_t ret = IRQ_NONE;
	int left;
	u32 reg;

	left = evt->count;

	if (!(evt->flags & DWC3_EVENT_PENDING))
		return IRQ_NONE;

	while (left > 0) {
		union dwc3_event event;

		event.raw = *(u32 *) (evt->cache + evt->lpos);

		dwc3_process_event_entry(dwc, &event);

		/*
		 * FIXME we wrap around correctly to the next entry as
		 * almost all entries are 4 bytes in size. There is one
		 * entry which has 12 bytes which is a regular entry
		 * followed by 8 bytes data. ATM I don't know how
		 * things are organized if we get next to the a
		 * boundary so I worry about that once we try to handle
		 * that.
		 */
		evt->lpos = (evt->lpos + 4) % evt->length;
		left -= 4;
	}

	evt->count = 0;
	evt->flags &= ~DWC3_EVENT_PENDING;
	ret = IRQ_HANDLED;

	/* Unmask interrupt */
	reg = dwc3_readl(dwc->regs, DWC3_GEVNTSIZ(0));
	reg &= ~DWC3_GEVNTSIZ_INTMASK;
	dwc3_writel(dwc->regs, DWC3_GEVNTSIZ(0), reg);

	if (dwc->imod_interval) {
		dwc3_writel(dwc->regs, DWC3_GEVNTCOUNT(0), DWC3_GEVNTCOUNT_EHB);
		dwc3_writel(dwc->regs, DWC3_DEV_IMOD(0), dwc->imod_interval);
	}

	return ret;
}