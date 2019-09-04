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
typedef  int u32 ;
struct iss_csi2_device {int /*<<< orphan*/  regs1; int /*<<< orphan*/  iss; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_IRQENABLE ; 
 int /*<<< orphan*/  CSI2_IRQSTATUS ; 
 int CSI2_IRQ_COMPLEXIO_ERR ; 
 int CSI2_IRQ_CONTEXT0 ; 
 int CSI2_IRQ_ECC_CORRECTION ; 
 int CSI2_IRQ_ECC_NO_CORRECTION ; 
 int CSI2_IRQ_FIFO_OVF ; 
 int CSI2_IRQ_OCP_ERR ; 
 int CSI2_IRQ_SHORT_PACKET ; 
 int /*<<< orphan*/  iss_reg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iss_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void csi2_irq_status_set(struct iss_csi2_device *csi2, int enable)
{
	u32 reg;

	reg = CSI2_IRQ_OCP_ERR |
		CSI2_IRQ_SHORT_PACKET |
		CSI2_IRQ_ECC_CORRECTION |
		CSI2_IRQ_ECC_NO_CORRECTION |
		CSI2_IRQ_COMPLEXIO_ERR |
		CSI2_IRQ_FIFO_OVF |
		CSI2_IRQ_CONTEXT0;
	iss_reg_write(csi2->iss, csi2->regs1, CSI2_IRQSTATUS, reg);
	if (enable)
		iss_reg_set(csi2->iss, csi2->regs1, CSI2_IRQENABLE, reg);
	else
		iss_reg_write(csi2->iss, csi2->regs1, CSI2_IRQENABLE, 0);
}