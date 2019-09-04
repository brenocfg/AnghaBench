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
struct target_control {int heads; int sectors; int drv_flags; } ;
struct scsi_device {size_t id; TYPE_1__* host; } ;
struct initio_host {struct target_control* targets; } ;
struct block_device {int dummy; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int TCF_DRV_255_63 ; 

__attribute__((used)) static int i91u_biosparam(struct scsi_device *sdev, struct block_device *dev,
		sector_t capacity, int *info_array)
{
	struct initio_host *host;		/* Point to Host adapter control block */
	struct target_control *tc;

	host = (struct initio_host *) sdev->host->hostdata;
	tc = &host->targets[sdev->id];

	if (tc->heads) {
		info_array[0] = tc->heads;
		info_array[1] = tc->sectors;
		info_array[2] = (unsigned long)capacity / tc->heads / tc->sectors;
	} else {
		if (tc->drv_flags & TCF_DRV_255_63) {
			info_array[0] = 255;
			info_array[1] = 63;
			info_array[2] = (unsigned long)capacity / 255 / 63;
		} else {
			info_array[0] = 64;
			info_array[1] = 32;
			info_array[2] = (unsigned long)capacity >> 11;
		}
	}

#if defined(DEBUG_BIOSPARAM)
	if (i91u_debug & debug_biosparam) {
		printk("bios geometry: head=%d, sec=%d, cyl=%d\n",
		       info_array[0], info_array[1], info_array[2]);
		printk("WARNING: check, if the bios geometry is correct.\n");
	}
#endif

	return 0;
}