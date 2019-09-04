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
typedef  void* u32 ;
struct ccw_request {struct ccw1* cp; } ;
struct ccw_device {TYPE_1__* private; } ;
struct ccw1 {int count; scalar_t__ flags; void* cda; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ addr_t ;
struct TYPE_2__ {struct ccw1* iccws; struct ccw_request req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_RELEASE ; 
 int /*<<< orphan*/  CCW_CMD_STLCK ; 
 scalar_t__ CCW_FLAG_CC ; 

__attribute__((used)) static void stlck_build_cp(struct ccw_device *cdev, void *buf1, void *buf2)
{
	struct ccw_request *req = &cdev->private->req;
	struct ccw1 *cp = cdev->private->iccws;

	cp[0].cmd_code = CCW_CMD_STLCK;
	cp[0].cda = (u32) (addr_t) buf1;
	cp[0].count = 32;
	cp[0].flags = CCW_FLAG_CC;
	cp[1].cmd_code = CCW_CMD_RELEASE;
	cp[1].cda = (u32) (addr_t) buf2;
	cp[1].count = 32;
	cp[1].flags = 0;
	req->cp = cp;
}