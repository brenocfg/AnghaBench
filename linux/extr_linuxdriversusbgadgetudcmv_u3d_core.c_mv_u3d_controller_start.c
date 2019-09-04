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
struct mv_u3d {TYPE_2__* op_regs; int /*<<< orphan*/  dev; TYPE_1__* vuc_regs; scalar_t__ vbus_valid_detect; } ;
struct TYPE_4__ {int /*<<< orphan*/  usbcmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctrlepenable; int /*<<< orphan*/  intrenable; int /*<<< orphan*/  ltssm; } ;

/* Variables and functions */
 int MV_U3D_CMD_RUN_STOP ; 
 int MV_U3D_INTR_ENABLE_LINK_CHG ; 
 int MV_U3D_INTR_ENABLE_RXDESC_ERR ; 
 int MV_U3D_INTR_ENABLE_RX_COMPLETE ; 
 int MV_U3D_INTR_ENABLE_SETUP ; 
 int MV_U3D_INTR_ENABLE_TXDESC_ERR ; 
 int MV_U3D_INTR_ENABLE_TX_COMPLETE ; 
 int MV_U3D_INTR_ENABLE_VBUS_VALID ; 
 int MV_U3D_LTSSM_PHY_INIT_DONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mv_u3d_controller_start(struct mv_u3d *u3d)
{
	u32 usbintr;
	u32 temp;

	/* enable link LTSSM state machine */
	temp = ioread32(&u3d->vuc_regs->ltssm);
	temp |= MV_U3D_LTSSM_PHY_INIT_DONE;
	iowrite32(temp, &u3d->vuc_regs->ltssm);

	/* Enable interrupts */
	usbintr = MV_U3D_INTR_ENABLE_LINK_CHG | MV_U3D_INTR_ENABLE_TXDESC_ERR |
		MV_U3D_INTR_ENABLE_RXDESC_ERR | MV_U3D_INTR_ENABLE_TX_COMPLETE |
		MV_U3D_INTR_ENABLE_RX_COMPLETE | MV_U3D_INTR_ENABLE_SETUP |
		(u3d->vbus_valid_detect ? MV_U3D_INTR_ENABLE_VBUS_VALID : 0);
	iowrite32(usbintr, &u3d->vuc_regs->intrenable);

	/* Enable ctrl ep */
	iowrite32(0x1, &u3d->vuc_regs->ctrlepenable);

	/* Set the Run bit in the command register */
	iowrite32(MV_U3D_CMD_RUN_STOP, &u3d->op_regs->usbcmd);
	dev_dbg(u3d->dev, "after u3d_start, USBCMD 0x%x\n",
		ioread32(&u3d->op_regs->usbcmd));
}