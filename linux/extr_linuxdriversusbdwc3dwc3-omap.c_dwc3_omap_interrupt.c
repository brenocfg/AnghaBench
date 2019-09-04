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
struct dwc3_omap {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  dwc3_omap_disable_irqs (struct dwc3_omap*) ; 
 scalar_t__ dwc3_omap_read_irq0_status (struct dwc3_omap*) ; 
 scalar_t__ dwc3_omap_read_irqmisc_status (struct dwc3_omap*) ; 

__attribute__((used)) static irqreturn_t dwc3_omap_interrupt(int irq, void *_omap)
{
	struct dwc3_omap	*omap = _omap;

	if (dwc3_omap_read_irqmisc_status(omap) ||
	    dwc3_omap_read_irq0_status(omap)) {
		/* mask irqs */
		dwc3_omap_disable_irqs(omap);
		return IRQ_WAKE_THREAD;
	}

	return IRQ_NONE;
}