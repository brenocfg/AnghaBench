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
struct scsi_device {int /*<<< orphan*/  tagged_supported; } ;

/* Variables and functions */
 int scsi_change_queue_depth (struct scsi_device*,int) ; 

__attribute__((used)) static int pvscsi_change_queue_depth(struct scsi_device *sdev, int qdepth)
{
	if (!sdev->tagged_supported)
		qdepth = 1;
	return scsi_change_queue_depth(sdev, qdepth);
}