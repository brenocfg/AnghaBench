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
struct mmphw_ctrl {scalar_t__ reg_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SPU_IRQ_ENA ; 
 scalar_t__ SPU_IRQ_ISR ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t ctrl_handle_irq(int irq, void *dev_id)
{
	struct mmphw_ctrl *ctrl = (struct mmphw_ctrl *)dev_id;
	u32 isr, imask, tmp;

	isr = readl_relaxed(ctrl->reg_base + SPU_IRQ_ISR);
	imask = readl_relaxed(ctrl->reg_base + SPU_IRQ_ENA);

	do {
		/* clear clock only */
		tmp = readl_relaxed(ctrl->reg_base + SPU_IRQ_ISR);
		if (tmp & isr)
			writel_relaxed(~isr, ctrl->reg_base + SPU_IRQ_ISR);
	} while ((isr = readl_relaxed(ctrl->reg_base + SPU_IRQ_ISR)) & imask);

	return IRQ_HANDLED;
}