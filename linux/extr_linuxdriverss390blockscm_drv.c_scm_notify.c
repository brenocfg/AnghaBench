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
struct scm_device {scalar_t__ address; int /*<<< orphan*/  dev; } ;
struct scm_blk_dev {int dummy; } ;
typedef  enum scm_event { ____Placeholder_scm_event } scm_event ;

/* Variables and functions */
#define  SCM_AVAIL 129 
#define  SCM_CHANGE 128 
 int /*<<< orphan*/  SCM_LOG (int,char*) ; 
 int /*<<< orphan*/  SCM_LOG_STATE (int,struct scm_device*) ; 
 struct scm_blk_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long) ; 
 int /*<<< orphan*/  scm_blk_set_available (struct scm_blk_dev*) ; 

__attribute__((used)) static void scm_notify(struct scm_device *scmdev, enum scm_event event)
{
	struct scm_blk_dev *bdev = dev_get_drvdata(&scmdev->dev);

	switch (event) {
	case SCM_CHANGE:
		pr_info("%lx: The capabilities of the SCM increment changed\n",
			(unsigned long) scmdev->address);
		SCM_LOG(2, "State changed");
		SCM_LOG_STATE(2, scmdev);
		break;
	case SCM_AVAIL:
		SCM_LOG(2, "Increment available");
		SCM_LOG_STATE(2, scmdev);
		scm_blk_set_available(bdev);
		break;
	}
}