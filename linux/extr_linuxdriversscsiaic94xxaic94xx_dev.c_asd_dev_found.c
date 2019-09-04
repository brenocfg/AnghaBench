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
struct domain_device {int dev_type; int /*<<< orphan*/  tproto; TYPE_2__* port; } ;
struct TYPE_6__ {int /*<<< orphan*/  ddb_lock; } ;
struct asd_ha_struct {TYPE_3__ hw_prof; } ;
struct TYPE_5__ {TYPE_1__* ha; } ;
struct TYPE_4__ {struct asd_ha_struct* lldd_ha; } ;

/* Variables and functions */
#define  SAS_SATA_PM 129 
#define  SAS_SATA_PM_PORT 128 
 int asd_init_initiator_ddb (struct domain_device*) ; 
 int asd_init_sata_pm_ddb (struct domain_device*) ; 
 int asd_init_sata_pm_port_ddb (struct domain_device*) ; 
 int asd_init_target_ddb (struct domain_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int asd_dev_found(struct domain_device *dev)
{
	unsigned long flags;
	int res = 0;
	struct asd_ha_struct *asd_ha = dev->port->ha->lldd_ha;

	spin_lock_irqsave(&asd_ha->hw_prof.ddb_lock, flags);
	switch (dev->dev_type) {
	case SAS_SATA_PM:
		res = asd_init_sata_pm_ddb(dev);
		break;
	case SAS_SATA_PM_PORT:
		res = asd_init_sata_pm_port_ddb(dev);
		break;
	default:
		if (dev->tproto)
			res = asd_init_target_ddb(dev);
		else
			res = asd_init_initiator_ddb(dev);
	}
	spin_unlock_irqrestore(&asd_ha->hw_prof.ddb_lock, flags);

	return res;
}