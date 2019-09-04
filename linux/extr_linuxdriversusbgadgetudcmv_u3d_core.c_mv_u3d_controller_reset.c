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
typedef  int u32 ;
struct mv_u3d {int ep_context_dma; TYPE_1__* op_regs; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dcbaaph; int /*<<< orphan*/  dcbaapl; int /*<<< orphan*/  usbcmd; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned int LOOPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOPS_USEC ; 
 int MV_U3D_CMD_CTRL_RESET ; 
 int MV_U3D_CMD_RUN_STOP ; 
 int /*<<< orphan*/  MV_U3D_RESET_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv_u3d_controller_reset(struct mv_u3d *u3d)
{
	unsigned int loops;
	u32 tmp;

	/* Stop the controller */
	tmp = ioread32(&u3d->op_regs->usbcmd);
	tmp &= ~MV_U3D_CMD_RUN_STOP;
	iowrite32(tmp, &u3d->op_regs->usbcmd);

	/* Reset the controller to get default values */
	iowrite32(MV_U3D_CMD_CTRL_RESET, &u3d->op_regs->usbcmd);

	/* wait for reset to complete */
	loops = LOOPS(MV_U3D_RESET_TIMEOUT);
	while (ioread32(&u3d->op_regs->usbcmd) & MV_U3D_CMD_CTRL_RESET) {
		if (loops == 0) {
			dev_err(u3d->dev,
				"Wait for RESET completed TIMEOUT\n");
			return -ETIMEDOUT;
		}
		loops--;
		udelay(LOOPS_USEC);
	}

	/* Configure the Endpoint Context Address */
	iowrite32(u3d->ep_context_dma, &u3d->op_regs->dcbaapl);
	iowrite32(0, &u3d->op_regs->dcbaaph);

	return 0;
}