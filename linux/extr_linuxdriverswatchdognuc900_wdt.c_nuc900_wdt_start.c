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
struct TYPE_2__ {int /*<<< orphan*/  timer; scalar_t__ next_heartbeat; int /*<<< orphan*/  wdt_lock; scalar_t__ wdt_base; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ REG_WTCR ; 
 int WDT_HW_TIMEOUT ; 
 scalar_t__ WDT_TIMEOUT ; 
 unsigned int WTCLK ; 
 unsigned int WTE ; 
 unsigned int WTIF ; 
 unsigned int WTIS ; 
 unsigned int WTR ; 
 unsigned int WTRE ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int heartbeat ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* nuc900_wdt ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void nuc900_wdt_start(void)
{
	unsigned int val;

	spin_lock(&nuc900_wdt->wdt_lock);

	val = __raw_readl(nuc900_wdt->wdt_base + REG_WTCR);
	val |= (WTRE | WTE | WTR | WTCLK | WTIF);
	val &= ~WTIS;
	val |= (WDT_HW_TIMEOUT << 0x04);
	__raw_writel(val, nuc900_wdt->wdt_base + REG_WTCR);

	spin_unlock(&nuc900_wdt->wdt_lock);

	nuc900_wdt->next_heartbeat = jiffies + heartbeat * HZ;
	mod_timer(&nuc900_wdt->timer, jiffies + WDT_TIMEOUT);
}