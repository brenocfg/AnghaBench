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
struct img_spfi {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SPFI_INTERRUPT_CLEAR ; 
 int SPFI_INTERRUPT_IACCESS ; 
 int /*<<< orphan*/  SPFI_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int spfi_readl (struct img_spfi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spfi_writel (struct img_spfi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t img_spfi_irq(int irq, void *dev_id)
{
	struct img_spfi *spfi = (struct img_spfi *)dev_id;
	u32 status;

	status = spfi_readl(spfi, SPFI_INTERRUPT_STATUS);
	if (status & SPFI_INTERRUPT_IACCESS) {
		spfi_writel(spfi, SPFI_INTERRUPT_IACCESS, SPFI_INTERRUPT_CLEAR);
		dev_err(spfi->dev, "Illegal access interrupt");
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}