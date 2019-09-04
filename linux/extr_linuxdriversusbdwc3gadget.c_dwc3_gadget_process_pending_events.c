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
struct dwc3 {int pending_events; int /*<<< orphan*/  irq_gadget; int /*<<< orphan*/  ev_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc3_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

void dwc3_gadget_process_pending_events(struct dwc3 *dwc)
{
	if (dwc->pending_events) {
		dwc3_interrupt(dwc->irq_gadget, dwc->ev_buf);
		dwc->pending_events = false;
		enable_irq(dwc->irq_gadget);
	}
}