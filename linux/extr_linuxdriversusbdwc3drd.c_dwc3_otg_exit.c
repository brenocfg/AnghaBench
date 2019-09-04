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
struct dwc3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_OTG_ALL_EVENTS ; 
 int /*<<< orphan*/  dwc3_otg_clear_events (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_otg_disable_events (struct dwc3*,int /*<<< orphan*/ ) ; 

void dwc3_otg_exit(struct dwc3 *dwc)
{
	/* disable all OTG IRQs */
	dwc3_otg_disable_events(dwc, DWC3_OTG_ALL_EVENTS);
	/* clear all events */
	dwc3_otg_clear_events(dwc);
}