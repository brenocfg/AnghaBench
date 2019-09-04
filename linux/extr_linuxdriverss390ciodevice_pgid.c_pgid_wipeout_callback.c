#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ccw_device {TYPE_2__* private; } ;
struct TYPE_3__ {scalar_t__ pgid_unknown; } ;
struct TYPE_4__ {TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  verify_done (struct ccw_device*,int) ; 
 int /*<<< orphan*/  verify_start (struct ccw_device*) ; 

__attribute__((used)) static void pgid_wipeout_callback(struct ccw_device *cdev, void *data, int rc)
{
	if (rc) {
		/* We don't know the path groups' state. Abort. */
		verify_done(cdev, rc);
		return;
	}
	/*
	 * Path groups have been reset. Restart path verification but
	 * leave paths in path_noirq_mask out.
	 */
	cdev->private->flags.pgid_unknown = 0;
	verify_start(cdev);
}