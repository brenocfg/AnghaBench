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
struct TYPE_5__ {int /*<<< orphan*/  shost; } ;
struct sas_ha_struct {TYPE_2__ core; int /*<<< orphan*/  lock; int /*<<< orphan*/  eh_wait_q; } ;
struct TYPE_4__ {int /*<<< orphan*/  ap; } ;
struct domain_device {int /*<<< orphan*/  state; TYPE_1__ sata_dev; TYPE_3__* port; } ;
struct TYPE_6__ {struct sas_ha_struct* ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAS_DEV_EH_PENDING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  ata_port_wait_eh (int /*<<< orphan*/ ) ; 
 scalar_t__ dev_is_sata (struct domain_device*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ scsi_host_in_recovery (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void sas_wait_eh(struct domain_device *dev)
{
	struct sas_ha_struct *ha = dev->port->ha;
	DEFINE_WAIT(wait);

	if (dev_is_sata(dev)) {
		ata_port_wait_eh(dev->sata_dev.ap);
		return;
	}
 retry:
	spin_lock_irq(&ha->lock);

	while (test_bit(SAS_DEV_EH_PENDING, &dev->state)) {
		prepare_to_wait(&ha->eh_wait_q, &wait, TASK_UNINTERRUPTIBLE);
		spin_unlock_irq(&ha->lock);
		schedule();
		spin_lock_irq(&ha->lock);
	}
	finish_wait(&ha->eh_wait_q, &wait);

	spin_unlock_irq(&ha->lock);

	/* make sure SCSI EH is complete */
	if (scsi_host_in_recovery(ha->core.shost)) {
		msleep(10);
		goto retry;
	}
}