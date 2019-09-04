#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int /*<<< orphan*/ * hostdata; TYPE_1__* host; } ;
struct ipr_resource_entry {TYPE_5__* sata_port; int /*<<< orphan*/ * sdev; } ;
struct ipr_ioa_cfg {TYPE_6__* host; } ;
struct TYPE_12__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_11__ {TYPE_4__* ap; } ;
struct TYPE_9__ {TYPE_2__* device; } ;
struct TYPE_10__ {TYPE_3__ link; } ;
struct TYPE_8__ {int /*<<< orphan*/  class; } ;
struct TYPE_7__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DEV_NONE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void ipr_slave_destroy(struct scsi_device *sdev)
{
	struct ipr_resource_entry *res;
	struct ipr_ioa_cfg *ioa_cfg;
	unsigned long lock_flags = 0;

	ioa_cfg = (struct ipr_ioa_cfg *) sdev->host->hostdata;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	res = (struct ipr_resource_entry *) sdev->hostdata;
	if (res) {
		if (res->sata_port)
			res->sata_port->ap->link.device[0].class = ATA_DEV_NONE;
		sdev->hostdata = NULL;
		res->sdev = NULL;
		res->sata_port = NULL;
	}
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
}