#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iss_csi2_device {int /*<<< orphan*/  regs1; TYPE_2__* iss; TYPE_1__* phy; int /*<<< orphan*/  available; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  phy_regs; scalar_t__ phy_in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_COMPLEXIO_CFG ; 
 int /*<<< orphan*/  CSI2_COMPLEXIO_CFG_RESET_CTRL ; 
 int /*<<< orphan*/  CSI2_SYSCONFIG ; 
 int CSI2_SYSCONFIG_AUTO_IDLE ; 
 int CSI2_SYSCONFIG_MSTANDBY_MODE_MASK ; 
 int /*<<< orphan*/  CSI2_SYSCONFIG_MSTANDBY_MODE_NO ; 
 int /*<<< orphan*/  CSI2_SYSCONFIG_SOFT_RESET ; 
 int /*<<< orphan*/  CSI2_SYSSTATUS ; 
 int CSI2_SYSSTATUS_RESET_DONE ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  REGISTER1 ; 
 int REGISTER1_RESET_DONE_CTRLCLK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int iss_poll_condition_timeout (int,int,int,int) ; 
 int iss_reg_read (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_set (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_update (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int omap4iss_csi2_reset(struct iss_csi2_device *csi2)
{
	unsigned int timeout;

	if (!csi2->available)
		return -ENODEV;

	if (csi2->phy->phy_in_use)
		return -EBUSY;

	iss_reg_set(csi2->iss, csi2->regs1, CSI2_SYSCONFIG,
		    CSI2_SYSCONFIG_SOFT_RESET);

	timeout = iss_poll_condition_timeout(
		iss_reg_read(csi2->iss, csi2->regs1, CSI2_SYSSTATUS) &
		CSI2_SYSSTATUS_RESET_DONE, 500, 100, 200);
	if (timeout) {
		dev_err(csi2->iss->dev, "CSI2: Soft reset timeout!\n");
		return -EBUSY;
	}

	iss_reg_set(csi2->iss, csi2->regs1, CSI2_COMPLEXIO_CFG,
		    CSI2_COMPLEXIO_CFG_RESET_CTRL);

	timeout = iss_poll_condition_timeout(
		iss_reg_read(csi2->iss, csi2->phy->phy_regs, REGISTER1) &
		REGISTER1_RESET_DONE_CTRLCLK, 10000, 100, 500);
	if (timeout) {
		dev_err(csi2->iss->dev, "CSI2: CSI2_96M_FCLK reset timeout!\n");
		return -EBUSY;
	}

	iss_reg_update(csi2->iss, csi2->regs1, CSI2_SYSCONFIG,
		       CSI2_SYSCONFIG_MSTANDBY_MODE_MASK |
		       CSI2_SYSCONFIG_AUTO_IDLE,
		       CSI2_SYSCONFIG_MSTANDBY_MODE_NO);

	return 0;
}