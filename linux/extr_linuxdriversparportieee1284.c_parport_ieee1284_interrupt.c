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
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  parport_ieee1284_wakeup (struct parport*) ; 

void parport_ieee1284_interrupt (void *handle)
{
	struct parport *port = handle;
	parport_ieee1284_wakeup (port);

#ifdef CONFIG_PARPORT_1284
	if (port->ieee1284.phase == IEEE1284_PH_REV_IDLE) {
		/* An interrupt in this phase means that data
		 * is now available. */
		DPRINTK (KERN_DEBUG "%s: Data available\n", port->name);
		parport_ieee1284_ack_data_avail (port);
	}
#endif /* IEEE1284 support */
}