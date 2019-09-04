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
 unsigned int EVTCHN_ROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_evtchn_to_irq_row (unsigned int) ; 
 int /*<<< orphan*/ ** evtchn_to_irq ; 
 int /*<<< orphan*/  xen_evtchn_max_channels () ; 

__attribute__((used)) static void clear_evtchn_to_irq_all(void)
{
	unsigned row;

	for (row = 0; row < EVTCHN_ROW(xen_evtchn_max_channels()); row++) {
		if (evtchn_to_irq[row] == NULL)
			continue;
		clear_evtchn_to_irq_row(row);
	}
}