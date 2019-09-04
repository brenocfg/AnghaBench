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

/* Variables and functions */
 size_t EVTCHN_COL (unsigned int) ; 
 size_t EVTCHN_ROW (unsigned int) ; 
 int** evtchn_to_irq ; 
 unsigned int xen_evtchn_max_channels () ; 

int get_evtchn_to_irq(unsigned evtchn)
{
	if (evtchn >= xen_evtchn_max_channels())
		return -1;
	if (evtchn_to_irq[EVTCHN_ROW(evtchn)] == NULL)
		return -1;
	return evtchn_to_irq[EVTCHN_ROW(evtchn)][EVTCHN_COL(evtchn)];
}