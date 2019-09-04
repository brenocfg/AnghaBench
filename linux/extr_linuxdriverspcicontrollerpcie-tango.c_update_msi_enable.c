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
struct tango_pcie {int base; int /*<<< orphan*/  used_msi_lock; } ;
struct irq_data {int hwirq; struct tango_pcie* chip_data; } ;

/* Variables and functions */
 int BIT (int) ; 
 int SMP8759_ENABLE ; 
 int readl_relaxed (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int,int) ; 

__attribute__((used)) static void update_msi_enable(struct irq_data *d, bool unmask)
{
	unsigned long flags;
	struct tango_pcie *pcie = d->chip_data;
	u32 offset = (d->hwirq / 32) * 4;
	u32 bit = BIT(d->hwirq % 32);
	u32 val;

	spin_lock_irqsave(&pcie->used_msi_lock, flags);
	val = readl_relaxed(pcie->base + SMP8759_ENABLE + offset);
	val = unmask ? val | bit : val & ~bit;
	writel_relaxed(val, pcie->base + SMP8759_ENABLE + offset);
	spin_unlock_irqrestore(&pcie->used_msi_lock, flags);
}