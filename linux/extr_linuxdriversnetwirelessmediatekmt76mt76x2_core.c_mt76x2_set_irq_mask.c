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
typedef  int /*<<< orphan*/  u32 ;
struct mt76x2_dev {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  irqmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_INT_MASK_CSR ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mt76x2_set_irq_mask(struct mt76x2_dev *dev, u32 clear, u32 set)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->irq_lock, flags);
	dev->irqmask &= ~clear;
	dev->irqmask |= set;
	mt76_wr(dev, MT_INT_MASK_CSR, dev->irqmask);
	spin_unlock_irqrestore(&dev->irq_lock, flags);
}