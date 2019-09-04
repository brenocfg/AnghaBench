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
struct device {int dummy; } ;
struct attribute_container {int /*<<< orphan*/ * class; } ;
struct Scsi_Host {TYPE_2__* transportt; } ;
struct TYPE_6__ {int /*<<< orphan*/  class; } ;
struct TYPE_4__ {struct attribute_container ac; } ;
struct TYPE_5__ {TYPE_1__ host_attrs; } ;

/* Variables and functions */
 struct Scsi_Host* dev_to_shost (struct device*) ; 
 int /*<<< orphan*/  scsi_is_host_device (struct device*) ; 
 TYPE_3__ spi_host_class ; 

__attribute__((used)) static int spi_host_match(struct attribute_container *cont,
			  struct device *dev)
{
	struct Scsi_Host *shost;

	if (!scsi_is_host_device(dev))
		return 0;

	shost = dev_to_shost(dev);
	if (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &spi_host_class.class)
		return 0;

	return &shost->transportt->host_attrs.ac == cont;
}