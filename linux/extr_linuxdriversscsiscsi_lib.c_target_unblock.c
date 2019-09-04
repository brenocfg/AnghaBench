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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unblock ; 
 scalar_t__ scsi_is_target_device (struct device*) ; 
 int /*<<< orphan*/  starget_for_each_device (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_scsi_target (struct device*) ; 

__attribute__((used)) static int
target_unblock(struct device *dev, void *data)
{
	if (scsi_is_target_device(dev))
		starget_for_each_device(to_scsi_target(dev), data,
					device_unblock);
	return 0;
}