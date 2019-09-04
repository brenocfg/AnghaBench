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
 unsigned int EVTCHN_PER_ROW ; 
 int** evtchn_to_irq ; 

__attribute__((used)) static void clear_evtchn_to_irq_row(unsigned row)
{
	unsigned col;

	for (col = 0; col < EVTCHN_PER_ROW; col++)
		evtchn_to_irq[row][col] = -1;
}