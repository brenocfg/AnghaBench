#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct parport {scalar_t__ cad; } ;
struct TYPE_2__ {scalar_t__ pardev; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 TYPE_1__ device ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parport_release (scalar_t__) ; 
 int /*<<< orphan*/  parport_unregister_device (scalar_t__) ; 

__attribute__((used)) static void parport_detach(struct parport *port)
{
	if (port->cad != device.pardev)
		return;	/* not our port */

	hrtimer_cancel(&device.timer);
	parport_release(device.pardev);
	parport_unregister_device(device.pardev);
}