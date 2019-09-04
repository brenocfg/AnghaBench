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
struct timer_list {int dummy; } ;
struct pxa25x_udc {scalar_t__ ep0state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DBG_VERBOSE ; 
 scalar_t__ EP0_STALL ; 
 int UDCCS0_FST ; 
 int UDCCS0_FTF ; 
 int UDCCS0_SST ; 
 struct pxa25x_udc* dev ; 
 struct pxa25x_udc* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  start_watchdog (struct pxa25x_udc*) ; 
 int /*<<< orphan*/  timer ; 
 int udc_ep0_get_UDCCS (struct pxa25x_udc*) ; 
 int /*<<< orphan*/  udc_ep0_set_UDCCS (struct pxa25x_udc*,int) ; 

__attribute__((used)) static void udc_watchdog(struct timer_list *t)
{
	struct pxa25x_udc	*dev = from_timer(dev, t, timer);

	local_irq_disable();
	if (dev->ep0state == EP0_STALL
			&& (udc_ep0_get_UDCCS(dev) & UDCCS0_FST) == 0
			&& (udc_ep0_get_UDCCS(dev) & UDCCS0_SST) == 0) {
		udc_ep0_set_UDCCS(dev, UDCCS0_FST|UDCCS0_FTF);
		DBG(DBG_VERBOSE, "ep0 re-stall\n");
		start_watchdog(dev);
	}
	local_irq_enable();
}