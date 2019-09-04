#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mv_u3d {TYPE_2__* op_regs; int /*<<< orphan*/  dev; TYPE_1__* vuc_regs; scalar_t__ vbus_valid_detect; int /*<<< orphan*/  clock_gating; } ;
struct TYPE_4__ {int /*<<< orphan*/  usbcmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  setuplock; int /*<<< orphan*/  linkchange; int /*<<< orphan*/  trbcomplete; int /*<<< orphan*/  trbunderrun; int /*<<< orphan*/  endcomplete; int /*<<< orphan*/  intrenable; } ;

/* Variables and functions */
 int MV_U3D_CMD_RUN_STOP ; 
 int MV_U3D_INTR_ENABLE_VBUS_VALID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mv_u3d_controller_stop(struct mv_u3d *u3d)
{
	u32 tmp;

	if (!u3d->clock_gating && u3d->vbus_valid_detect)
		iowrite32(MV_U3D_INTR_ENABLE_VBUS_VALID,
				&u3d->vuc_regs->intrenable);
	else
		iowrite32(0, &u3d->vuc_regs->intrenable);
	iowrite32(~0x0, &u3d->vuc_regs->endcomplete);
	iowrite32(~0x0, &u3d->vuc_regs->trbunderrun);
	iowrite32(~0x0, &u3d->vuc_regs->trbcomplete);
	iowrite32(~0x0, &u3d->vuc_regs->linkchange);
	iowrite32(0x1, &u3d->vuc_regs->setuplock);

	/* Reset the RUN bit in the command register to stop USB */
	tmp = ioread32(&u3d->op_regs->usbcmd);
	tmp &= ~MV_U3D_CMD_RUN_STOP;
	iowrite32(tmp, &u3d->op_regs->usbcmd);
	dev_dbg(u3d->dev, "after u3d_stop, USBCMD 0x%x\n",
		ioread32(&u3d->op_regs->usbcmd));
}