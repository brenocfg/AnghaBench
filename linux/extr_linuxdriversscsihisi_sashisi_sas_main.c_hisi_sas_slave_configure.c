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
struct domain_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_is_sata (struct domain_device*) ; 
 int /*<<< orphan*/  sas_change_queue_depth (struct scsi_device*,int) ; 
 int sas_slave_configure (struct scsi_device*) ; 
 struct domain_device* sdev_to_domain_dev (struct scsi_device*) ; 

int hisi_sas_slave_configure(struct scsi_device *sdev)
{
	struct domain_device *dev = sdev_to_domain_dev(sdev);
	int ret = sas_slave_configure(sdev);

	if (ret)
		return ret;
	if (!dev_is_sata(dev))
		sas_change_queue_depth(sdev, 64);

	return 0;
}