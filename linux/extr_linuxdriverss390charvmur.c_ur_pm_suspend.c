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
struct urdev {scalar_t__ open_flag; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  TRACE (char*,struct ccw_device*) ; 
 struct urdev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ur_banner ; 

__attribute__((used)) static int ur_pm_suspend(struct ccw_device *cdev)
{
	struct urdev *urd = dev_get_drvdata(&cdev->dev);

	TRACE("ur_pm_suspend: cdev=%p\n", cdev);
	if (urd->open_flag) {
		pr_err("Unit record device %s is busy, %s refusing to "
		       "suspend.\n", dev_name(&cdev->dev), ur_banner);
		return -EBUSY;
	}
	return 0;
}