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
struct uas_dev_info {int /*<<< orphan*/  data_urbs; int /*<<< orphan*/  sense_urbs; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int ETIME ; 
 int HZ ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  uas_cmnd_list_empty (struct uas_dev_info*) ; 
 int usb_wait_anchor_empty_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int uas_wait_for_pending_cmnds(struct uas_dev_info *devinfo)
{
	unsigned long start_time;
	int r;

	start_time = jiffies;
	do {
		flush_work(&devinfo->work);

		r = usb_wait_anchor_empty_timeout(&devinfo->sense_urbs, 5000);
		if (r == 0)
			return -ETIME;

		r = usb_wait_anchor_empty_timeout(&devinfo->data_urbs, 500);
		if (r == 0)
			return -ETIME;

		if (time_after(jiffies, start_time + 5 * HZ))
			return -ETIME;
	} while (!uas_cmnd_list_empty(devinfo));

	return 0;
}