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
struct st_modedef {scalar_t__* devs; scalar_t__* cdevs; } ;
struct scsi_tape {struct st_modedef* modes; TYPE_2__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ sdev_gendev; } ;

/* Variables and functions */
 int ST_NBR_MODES ; 
 int /*<<< orphan*/  cdev_del (scalar_t__) ; 
 int /*<<< orphan*/  device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void remove_cdevs(struct scsi_tape *tape)
{
	int mode, rew;
	sysfs_remove_link(&tape->device->sdev_gendev.kobj, "tape");
	for (mode = 0; mode < ST_NBR_MODES; mode++) {
		struct st_modedef *STm = &(tape->modes[mode]);
		for (rew = 0; rew < 2; rew++) {
			if (STm->cdevs[rew])
				cdev_del(STm->cdevs[rew]);
			if (STm->devs[rew])
				device_unregister(STm->devs[rew]);
		}
	}
}