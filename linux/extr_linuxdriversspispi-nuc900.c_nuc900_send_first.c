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
struct nuc900_spi {int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 unsigned int LSB ; 
 scalar_t__ USI_CNT ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nuc900_send_first(struct nuc900_spi *hw, unsigned int lsb)
{
	unsigned int val;
	unsigned long flags;

	spin_lock_irqsave(&hw->lock, flags);

	val = __raw_readl(hw->regs + USI_CNT);

	if (lsb)
		val |= LSB;
	else
		val &= ~LSB;
	__raw_writel(val, hw->regs + USI_CNT);

	spin_unlock_irqrestore(&hw->lock, flags);
}