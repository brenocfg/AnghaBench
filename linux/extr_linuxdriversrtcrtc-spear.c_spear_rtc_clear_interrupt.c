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
struct spear_rtc_config {int /*<<< orphan*/  lock; scalar_t__ ioaddr; } ;

/* Variables and functions */
 unsigned int RTC_INT_MASK ; 
 scalar_t__ STATUS_REG ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void spear_rtc_clear_interrupt(struct spear_rtc_config *config)
{
	unsigned int val;
	unsigned long flags;

	spin_lock_irqsave(&config->lock, flags);
	val = readl(config->ioaddr + STATUS_REG);
	val |= RTC_INT_MASK;
	writel(val, config->ioaddr + STATUS_REG);
	spin_unlock_irqrestore(&config->lock, flags);
}