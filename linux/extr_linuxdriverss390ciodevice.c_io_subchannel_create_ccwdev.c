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
 struct ccw_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct ccw_device*) ; 
 struct ccw_device* io_subchannel_allocate_dev (struct subchannel*) ; 
 int io_subchannel_initialize_dev (struct subchannel*,struct ccw_device*) ; 

__attribute__((used)) static struct ccw_device * io_subchannel_create_ccwdev(struct subchannel *sch)
{
	struct ccw_device *cdev;
	int ret;

	cdev = io_subchannel_allocate_dev(sch);
	if (!IS_ERR(cdev)) {
		ret = io_subchannel_initialize_dev(sch, cdev);
		if (ret)
			cdev = ERR_PTR(ret);
	}
	return cdev;
}