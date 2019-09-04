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
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ qla82xx_rom_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
ql82xx_rom_lock_d(struct qla_hw_data *ha)
{
	int loops = 0;
	uint32_t lock_owner = 0;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	while ((qla82xx_rom_lock(ha) != 0) && (loops < 50000)) {
		udelay(100);
		cond_resched();
		loops++;
	}
	if (loops >= 50000) {
		lock_owner = qla82xx_rd_32(ha, QLA82XX_ROM_LOCK_ID);
		ql_log(ql_log_warn, vha, 0xb010,
		    "ROM lock failed, Lock Owner %u.\n", lock_owner);
		return -1;
	}
	return 0;
}