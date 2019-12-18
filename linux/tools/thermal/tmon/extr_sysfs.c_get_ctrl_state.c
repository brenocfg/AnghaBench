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
struct TYPE_4__ {int nr_cooling_dev; TYPE_1__* cdi; } ;
struct TYPE_3__ {int flag; int instance; } ;

/* Variables and functions */
 char* CDEV ; 
 int CDEV_FLAG_IN_CONTROL ; 
 int /*<<< orphan*/  LOG_INFO ; 
 char* THERMAL_SYSFS ; 
 TYPE_2__ ptdata ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,int) ; 
 int /*<<< orphan*/  sysfs_get_ulong (char*,char*,unsigned long*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int) ; 

void get_ctrl_state(unsigned long *state)
{
	char ctrl_cdev_path[256];
	int ctrl_cdev_id = -1;
	int i;

	/* TODO: take average of all ctrl types. also consider change based on
	 * uevent. Take the first reading for now.
	 */
	for (i = 0; i < ptdata.nr_cooling_dev; i++) {
		if (ptdata.cdi[i].flag & CDEV_FLAG_IN_CONTROL) {
			ctrl_cdev_id = ptdata.cdi[i].instance;
			syslog(LOG_INFO, "ctrl cdev %d get state\n",
				ptdata.cdi[i].instance);
			break;
		}
	}
	if (ctrl_cdev_id == -1) {
		*state = 0;
		return;
	}
	snprintf(ctrl_cdev_path, 256, "%s/%s%d", THERMAL_SYSFS,
		CDEV, ctrl_cdev_id);
	sysfs_get_ulong(ctrl_cdev_path, "cur_state", state);
}