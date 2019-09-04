#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct parport {int /*<<< orphan*/  name; } ;
struct pardev_cb {int /*<<< orphan*/  flags; TYPE_1__* private; } ;
typedef  int /*<<< orphan*/  pps_cb ;
struct TYPE_7__ {int /*<<< orphan*/  function; } ;
struct TYPE_6__ {int /*<<< orphan*/  pardev; TYPE_2__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  PARPORT_FLAG_EXCL ; 
 int attached ; 
 int /*<<< orphan*/  calibrate_port (TYPE_1__*) ; 
 TYPE_1__ device ; 
 int /*<<< orphan*/  hrtimer_event ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pardev_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next_intr_time (TYPE_1__*) ; 
 scalar_t__ parport_claim_or_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_register_dev_model (struct parport*,int /*<<< orphan*/ ,struct pardev_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parport_attach(struct parport *port)
{
	struct pardev_cb pps_cb;

	if (attached) {
		/* we already have a port */
		return;
	}

	memset(&pps_cb, 0, sizeof(pps_cb));
	pps_cb.private = &device;
	pps_cb.flags = PARPORT_FLAG_EXCL;
	device.pardev = parport_register_dev_model(port, KBUILD_MODNAME,
						   &pps_cb, 0);
	if (!device.pardev) {
		pr_err("couldn't register with %s\n", port->name);
		return;
	}

	if (parport_claim_or_block(device.pardev) < 0) {
		pr_err("couldn't claim %s\n", port->name);
		goto err_unregister_dev;
	}

	pr_info("attached to %s\n", port->name);
	attached = 1;

	calibrate_port(&device);

	hrtimer_init(&device.timer, CLOCK_REALTIME, HRTIMER_MODE_ABS);
	device.timer.function = hrtimer_event;
	hrtimer_start(&device.timer, next_intr_time(&device), HRTIMER_MODE_ABS);

	return;

err_unregister_dev:
	parport_unregister_device(device.pardev);
}