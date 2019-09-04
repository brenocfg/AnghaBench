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
struct ccw_device {TYPE_1__* private; int /*<<< orphan*/  (* handler ) (struct ccw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  enum dev_event { ____Placeholder_dev_event } dev_event ;
struct TYPE_2__ {int /*<<< orphan*/  async_kill_io_rc; int /*<<< orphan*/  intparm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_online_verify (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_set_timeout (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ccw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ccw_device_killing_irq(struct ccw_device *cdev, enum dev_event dev_event)
{
	ccw_device_set_timeout(cdev, 0);
	/* Start delayed path verification. */
	ccw_device_online_verify(cdev, 0);
	/* OK, i/o is dead now. Call interrupt handler. */
	if (cdev->handler)
		cdev->handler(cdev, cdev->private->intparm,
			      ERR_PTR(cdev->private->async_kill_io_rc));
}