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
typedef  int /*<<< orphan*/  u32 ;
struct platform_device {int dummy; } ;
struct mv_u3d {TYPE_1__* op_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  usbcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV_U3D_CMD_RUN_STOP ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mv_u3d* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void mv_u3d_shutdown(struct platform_device *dev)
{
	struct mv_u3d *u3d = platform_get_drvdata(dev);
	u32 tmp;

	tmp = ioread32(&u3d->op_regs->usbcmd);
	tmp &= ~MV_U3D_CMD_RUN_STOP;
	iowrite32(tmp, &u3d->op_regs->usbcmd);
}