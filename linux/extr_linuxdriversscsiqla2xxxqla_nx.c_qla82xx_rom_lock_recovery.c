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
typedef  int /*<<< orphan*/  uint32_t ;
struct qla_hw_data {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA82XX_ROM_LOCK_ID ; 
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ qla82xx_rom_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_rom_unlock (struct qla_hw_data*) ; 

__attribute__((used)) static void
qla82xx_rom_lock_recovery(struct qla_hw_data *ha)
{
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);
	uint32_t lock_owner = 0;

	if (qla82xx_rom_lock(ha)) {
		lock_owner = qla82xx_rd_32(ha, QLA82XX_ROM_LOCK_ID);
		/* Someone else is holding the lock. */
		ql_log(ql_log_info, vha, 0xb022,
		    "Resetting rom_lock, Lock Owner %u.\n", lock_owner);
	}
	/*
	 * Either we got the lock, or someone
	 * else died while holding it.
	 * In either case, unlock.
	 */
	qla82xx_rom_unlock(ha);
}