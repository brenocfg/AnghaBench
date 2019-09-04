#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {TYPE_2__* host; } ;
struct gendisk {int dummy; } ;
struct TYPE_6__ {struct scsi_device* device; } ;
struct TYPE_5__ {TYPE_1__* hostt; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* unlock_native_capacity ) (struct scsi_device*) ;} ;

/* Variables and functions */
 TYPE_3__* scsi_disk (struct gendisk*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_device*) ; 

__attribute__((used)) static void sd_unlock_native_capacity(struct gendisk *disk)
{
	struct scsi_device *sdev = scsi_disk(disk)->device;

	if (sdev->host->hostt->unlock_native_capacity)
		sdev->host->hostt->unlock_native_capacity(sdev);
}