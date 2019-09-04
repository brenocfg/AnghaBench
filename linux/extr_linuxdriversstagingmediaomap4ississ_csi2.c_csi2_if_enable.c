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
typedef  scalar_t__ u8 ;
struct iss_csi2_ctrl_cfg {scalar_t__ if_enable; } ;
struct iss_csi2_device {int /*<<< orphan*/  regs1; int /*<<< orphan*/  iss; struct iss_csi2_ctrl_cfg ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_CTRL ; 
 int /*<<< orphan*/  CSI2_CTRL_IF_EN ; 
 int /*<<< orphan*/  iss_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csi2_if_enable(struct iss_csi2_device *csi2, u8 enable)
{
	struct iss_csi2_ctrl_cfg *currctrl = &csi2->ctrl;

	iss_reg_update(csi2->iss, csi2->regs1, CSI2_CTRL, CSI2_CTRL_IF_EN,
		       enable ? CSI2_CTRL_IF_EN : 0);

	currctrl->if_enable = enable;
}