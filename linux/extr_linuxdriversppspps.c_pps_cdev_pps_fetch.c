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
struct TYPE_2__ {int flags; unsigned long sec; unsigned long nsec; } ;
struct pps_fdata {TYPE_1__ timeout; } ;
struct pps_device {unsigned int last_ev; int /*<<< orphan*/  dev; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTARTSYS ; 
 int ETIMEDOUT ; 
 unsigned long HZ ; 
 unsigned long NSEC_PER_SEC ; 
 int PPS_TIME_INVALID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static int pps_cdev_pps_fetch(struct pps_device *pps, struct pps_fdata *fdata)
{
	unsigned int ev = pps->last_ev;
	int err = 0;

	/* Manage the timeout */
	if (fdata->timeout.flags & PPS_TIME_INVALID)
		err = wait_event_interruptible(pps->queue,
				ev != pps->last_ev);
	else {
		unsigned long ticks;

		dev_dbg(pps->dev, "timeout %lld.%09d\n",
				(long long) fdata->timeout.sec,
				fdata->timeout.nsec);
		ticks = fdata->timeout.sec * HZ;
		ticks += fdata->timeout.nsec / (NSEC_PER_SEC / HZ);

		if (ticks != 0) {
			err = wait_event_interruptible_timeout(
					pps->queue,
					ev != pps->last_ev,
					ticks);
			if (err == 0)
				return -ETIMEDOUT;
		}
	}

	/* Check for pending signals */
	if (err == -ERESTARTSYS) {
		dev_dbg(pps->dev, "pending signal caught\n");
		return -EINTR;
	}

	return 0;
}