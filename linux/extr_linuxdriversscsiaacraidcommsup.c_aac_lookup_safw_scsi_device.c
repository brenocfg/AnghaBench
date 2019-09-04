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
struct scsi_device {int dummy; } ;
struct aac_dev {int /*<<< orphan*/  scsi_host_ptr; } ;

/* Variables and functions */
 int CONTAINER_CHANNEL ; 
 int aac_phys_to_logical (int) ; 
 struct scsi_device* scsi_device_lookup (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct scsi_device *aac_lookup_safw_scsi_device(struct aac_dev *dev,
								int bus,
								int target)
{
	if (bus != CONTAINER_CHANNEL)
		bus = aac_phys_to_logical(bus);

	return scsi_device_lookup(dev->scsi_host_ptr, bus, target, 0);
}