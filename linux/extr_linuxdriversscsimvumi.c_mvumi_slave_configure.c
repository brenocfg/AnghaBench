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
struct scsi_device {unsigned char id; TYPE_1__* host; } ;
struct mvumi_hba {unsigned char max_target_id; int* target_map; } ;
struct TYPE_2__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int mvumi_slave_configure(struct scsi_device *sdev)
{
	struct mvumi_hba *mhba;
	unsigned char bitcount = sizeof(unsigned char) * 8;

	mhba = (struct mvumi_hba *) sdev->host->hostdata;
	if (sdev->id >= mhba->max_target_id)
		return -EINVAL;

	mhba->target_map[sdev->id / bitcount] |= (1 << (sdev->id % bitcount));
	return 0;
}