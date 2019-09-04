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
typedef  int /*<<< orphan*/  u32 ;
struct subchannel {int /*<<< orphan*/  schid; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {scalar_t__ online; TYPE_1__ dev; } ;
typedef  enum dev_event { ____Placeholder_dev_event } dev_event ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_STATE_NOT_OPER ; 
 int /*<<< orphan*/  ccw_device_done (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_online_verify (struct ccw_device*,int) ; 
 scalar_t__ cio_enable_subchannel (struct subchannel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_schedule_eval (int /*<<< orphan*/ ) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccw_device_boxed_verify(struct ccw_device *cdev,
				    enum dev_event dev_event)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);

	if (cdev->online) {
		if (cio_enable_subchannel(sch, (u32) (addr_t) sch))
			ccw_device_done(cdev, DEV_STATE_NOT_OPER);
		else
			ccw_device_online_verify(cdev, dev_event);
	} else
		css_schedule_eval(sch->schid);
}