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
typedef  int /*<<< orphan*/  u64 ;
struct scsi_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sas_address; } ;
struct TYPE_4__ {TYPE_1__ identify; } ;
struct sas_end_device {TYPE_2__ rphy; } ;

/* Variables and functions */
 struct sas_end_device* sas_sdev_to_rdev (struct scsi_device*) ; 

u64 sas_get_address(struct scsi_device *sdev)
{
	struct sas_end_device *rdev = sas_sdev_to_rdev(sdev);

	return rdev->rphy.identify.sas_address;
}