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
struct iss_device {int /*<<< orphan*/  dev; } ;
struct iss_csi2_device {int /*<<< orphan*/  regs1; int /*<<< orphan*/  available; struct iss_device* iss; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPLEXIO_CFG ; 
 int /*<<< orphan*/  COMPLEXIO_IRQENABLE ; 
 int /*<<< orphan*/  COMPLEXIO_IRQSTATUS ; 
 int /*<<< orphan*/  CSI2_PRINT_REGISTER (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTX_CTRL1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_CTRL2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_CTRL3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_DAT_OFST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_IRQENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_IRQSTATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_PING_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_PONG_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_H ; 
 int /*<<< orphan*/  DBG_P ; 
 int /*<<< orphan*/  IRQENABLE ; 
 int /*<<< orphan*/  IRQSTATUS ; 
 int /*<<< orphan*/  SHORT_PACKET ; 
 int /*<<< orphan*/  SYSCONFIG ; 
 int /*<<< orphan*/  SYSSTATUS ; 
 int /*<<< orphan*/  TIMING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void csi2_print_status(struct iss_csi2_device *csi2)
{
	struct iss_device *iss = csi2->iss;

	if (!csi2->available)
		return;

	dev_dbg(iss->dev, "-------------CSI2 Register dump-------------\n");

	CSI2_PRINT_REGISTER(iss, csi2->regs1, SYSCONFIG);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, SYSSTATUS);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, IRQENABLE);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, IRQSTATUS);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTRL);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, DBG_H);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, COMPLEXIO_CFG);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, COMPLEXIO_IRQSTATUS);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, SHORT_PACKET);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, COMPLEXIO_IRQENABLE);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, DBG_P);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, TIMING);
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_CTRL1(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_CTRL2(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_DAT_OFST(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_PING_ADDR(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_PONG_ADDR(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_IRQENABLE(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_IRQSTATUS(0));
	CSI2_PRINT_REGISTER(iss, csi2->regs1, CTX_CTRL3(0));

	dev_dbg(iss->dev, "--------------------------------------------\n");
}