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
typedef  int /*<<< orphan*/  u32 ;
struct dwc3_event_buffer {int flags; scalar_t__ buf; scalar_t__ cache; scalar_t__ lpos; scalar_t__ length; int /*<<< orphan*/  count; struct dwc3* dwc; } ;
struct dwc3 {int pending_events; int /*<<< orphan*/  regs; int /*<<< orphan*/  irq_gadget; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DWC3_EVENT_PENDING ; 
 int /*<<< orphan*/  DWC3_GEVNTCOUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_GEVNTCOUNT_MASK ; 
 int /*<<< orphan*/  DWC3_GEVNTSIZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_GEVNTSIZ_INTMASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ ) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t dwc3_check_event_buf(struct dwc3_event_buffer *evt)
{
	struct dwc3 *dwc = evt->dwc;
	u32 amount;
	u32 count;
	u32 reg;

	if (pm_runtime_suspended(dwc->dev)) {
		pm_runtime_get(dwc->dev);
		disable_irq_nosync(dwc->irq_gadget);
		dwc->pending_events = true;
		return IRQ_HANDLED;
	}

	/*
	 * With PCIe legacy interrupt, test shows that top-half irq handler can
	 * be called again after HW interrupt deassertion. Check if bottom-half
	 * irq event handler completes before caching new event to prevent
	 * losing events.
	 */
	if (evt->flags & DWC3_EVENT_PENDING)
		return IRQ_HANDLED;

	count = dwc3_readl(dwc->regs, DWC3_GEVNTCOUNT(0));
	count &= DWC3_GEVNTCOUNT_MASK;
	if (!count)
		return IRQ_NONE;

	evt->count = count;
	evt->flags |= DWC3_EVENT_PENDING;

	/* Mask interrupt */
	reg = dwc3_readl(dwc->regs, DWC3_GEVNTSIZ(0));
	reg |= DWC3_GEVNTSIZ_INTMASK;
	dwc3_writel(dwc->regs, DWC3_GEVNTSIZ(0), reg);

	amount = min(count, evt->length - evt->lpos);
	memcpy(evt->cache + evt->lpos, evt->buf + evt->lpos, amount);

	if (amount < count)
		memcpy(evt->cache, evt->buf, count - amount);

	dwc3_writel(dwc->regs, DWC3_GEVNTCOUNT(0), count);

	return IRQ_WAKE_THREAD;
}