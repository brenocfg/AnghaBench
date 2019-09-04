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
struct mvumi_hw_regs {int /*<<< orphan*/  pciea_to_arm_drbl_reg; int /*<<< orphan*/  arm_to_pciea_msg1; int /*<<< orphan*/  enpointa_mask_reg; } ;
struct mvumi_hba {struct mvumi_hw_regs* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRBL_SOFT_RESET ; 
 scalar_t__ HANDSHAKE_DONESTATE ; 
 scalar_t__ ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvumi_reset(struct mvumi_hba *mhba)
{
	struct mvumi_hw_regs *regs = mhba->regs;

	iowrite32(0, regs->enpointa_mask_reg);
	if (ioread32(regs->arm_to_pciea_msg1) != HANDSHAKE_DONESTATE)
		return;

	iowrite32(DRBL_SOFT_RESET, regs->pciea_to_arm_drbl_reg);
}