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
struct scsi_device {scalar_t__ inq_periph_qual; scalar_t__ no_uld_attach; } ;
struct device_driver {int dummy; } ;
struct device {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 scalar_t__ SCSI_INQ_PQ_CON ; 
 int /*<<< orphan*/  scsi_dev_type ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int scsi_bus_match(struct device *dev, struct device_driver *gendrv)
{
	struct scsi_device *sdp;

	if (dev->type != &scsi_dev_type)
		return 0;

	sdp = to_scsi_device(dev);
	if (sdp->no_uld_attach)
		return 0;
	return (sdp->inq_periph_qual == SCSI_INQ_PQ_CON)? 1: 0;
}