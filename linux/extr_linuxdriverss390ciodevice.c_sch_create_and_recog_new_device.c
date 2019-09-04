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
struct subchannel {int dummy; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ccw_device*) ; 
 int /*<<< orphan*/  css_sch_device_unregister (struct subchannel*) ; 
 struct ccw_device* io_subchannel_create_ccwdev (struct subchannel*) ; 
 int /*<<< orphan*/  io_subchannel_recog (struct ccw_device*,struct subchannel*) ; 

__attribute__((used)) static void sch_create_and_recog_new_device(struct subchannel *sch)
{
	struct ccw_device *cdev;

	/* Need to allocate a new ccw device. */
	cdev = io_subchannel_create_ccwdev(sch);
	if (IS_ERR(cdev)) {
		/* OK, we did everything we could... */
		css_sch_device_unregister(sch);
		return;
	}
	/* Start recognition for the new ccw device. */
	io_subchannel_recog(cdev, sch);
}