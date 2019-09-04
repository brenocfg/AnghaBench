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
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int EVTCHN_COL (unsigned int) ; 
 unsigned int EVTCHN_ROW (unsigned int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clear_evtchn_to_irq_row (unsigned int) ; 
 int** evtchn_to_irq ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 unsigned int xen_evtchn_max_channels () ; 

__attribute__((used)) static int set_evtchn_to_irq(unsigned evtchn, unsigned irq)
{
	unsigned row;
	unsigned col;

	if (evtchn >= xen_evtchn_max_channels())
		return -EINVAL;

	row = EVTCHN_ROW(evtchn);
	col = EVTCHN_COL(evtchn);

	if (evtchn_to_irq[row] == NULL) {
		/* Unallocated irq entries return -1 anyway */
		if (irq == -1)
			return 0;

		evtchn_to_irq[row] = (int *)get_zeroed_page(GFP_KERNEL);
		if (evtchn_to_irq[row] == NULL)
			return -ENOMEM;

		clear_evtchn_to_irq_row(row);
	}

	evtchn_to_irq[row][col] = irq;
	return 0;
}