#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qla4_82xx_rom_lock (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_82xx_rom_unlock (struct scsi_qla_host*) ; 

void qla4_82xx_rom_lock_recovery(struct scsi_qla_host *ha)
{
	if (qla4_82xx_rom_lock(ha)) {
		/* Someone else is holding the lock. */
		dev_info(&ha->pdev->dev, "Resetting rom_lock\n");
	}

	/*
	 * Either we got the lock, or someone
	 * else died while holding it.
	 * In either case, unlock.
	 */
	qla4_82xx_rom_unlock(ha);
}