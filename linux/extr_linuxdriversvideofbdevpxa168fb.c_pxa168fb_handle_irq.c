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
struct pxa168fb_info {scalar_t__ reg_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int GRA_FRAME_IRQ0_ENA_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ SPU_IRQ_ISR ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t pxa168fb_handle_irq(int irq, void *dev_id)
{
	struct pxa168fb_info *fbi = dev_id;
	u32 isr = readl(fbi->reg_base + SPU_IRQ_ISR);

	if ((isr & GRA_FRAME_IRQ0_ENA_MASK)) {

		writel(isr & (~GRA_FRAME_IRQ0_ENA_MASK),
			fbi->reg_base + SPU_IRQ_ISR);

		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}