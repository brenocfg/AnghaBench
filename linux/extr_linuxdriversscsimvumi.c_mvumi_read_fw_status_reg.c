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
struct mvumi_hba {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  arm_to_pciea_drbl_reg; } ;

/* Variables and functions */
 unsigned int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int mvumi_read_fw_status_reg(struct mvumi_hba *mhba)
{
	unsigned int status;

	status = ioread32(mhba->regs->arm_to_pciea_drbl_reg);
	if (status)
		iowrite32(status, mhba->regs->arm_to_pciea_drbl_reg);
	return status;
}