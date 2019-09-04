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
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int get_evtchn_to_irq (unsigned int) ; 

__attribute__((used)) static void handle_irq_for_port(unsigned port)
{
	int irq;

	irq = get_evtchn_to_irq(port);
	if (irq != -1)
		generic_handle_irq(irq);
}