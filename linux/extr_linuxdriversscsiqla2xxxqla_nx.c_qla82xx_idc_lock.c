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
struct qla_hw_data {int dummy; } ;

/* Variables and functions */
 int IDC_LOCK_TIMEOUT ; 
 int /*<<< orphan*/  PCIE_SEM5_LOCK ; 
 int /*<<< orphan*/  QLA82XX_PCIE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 

int qla82xx_idc_lock(struct qla_hw_data *ha)
{
	int i;
	int done = 0, timeout = 0;

	while (!done) {
		/* acquire semaphore5 from PCI HW block */
		done = qla82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM5_LOCK));
		if (done == 1)
			break;
		if (timeout >= IDC_LOCK_TIMEOUT)
			return -1;

		timeout++;

		/* Yield CPU */
		if (!in_interrupt())
			schedule();
		else {
			for (i = 0; i < 20; i++)
				cpu_relax();
		}
	}

	return 0;
}