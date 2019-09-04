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
struct mvumi_hw_regs {unsigned int int_drbl_int_mask; unsigned int int_dl_cpu2pciea; int /*<<< orphan*/  enpointa_mask_reg; int /*<<< orphan*/  arm_to_pciea_mask_reg; int /*<<< orphan*/  arm_to_pciea_drbl_reg; } ;
struct mvumi_hba {struct mvumi_hw_regs* regs; } ;

/* Variables and functions */
 unsigned int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ mvumi_check_handshake (struct mvumi_hba*) ; 

__attribute__((used)) static unsigned char mvumi_start(struct mvumi_hba *mhba)
{
	unsigned int tmp;
	struct mvumi_hw_regs *regs = mhba->regs;

	/* clear Door bell */
	tmp = ioread32(regs->arm_to_pciea_drbl_reg);
	iowrite32(tmp, regs->arm_to_pciea_drbl_reg);

	iowrite32(regs->int_drbl_int_mask, regs->arm_to_pciea_mask_reg);
	tmp = ioread32(regs->enpointa_mask_reg) | regs->int_dl_cpu2pciea;
	iowrite32(tmp, regs->enpointa_mask_reg);
	msleep(100);
	if (mvumi_check_handshake(mhba))
		return -1;

	return 0;
}