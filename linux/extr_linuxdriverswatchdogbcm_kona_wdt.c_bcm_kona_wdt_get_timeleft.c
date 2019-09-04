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
struct watchdog_device {int dummy; } ;
struct bcm_kona_wdt {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int SECWDOG_COUNT_MASK ; 
 int /*<<< orphan*/  SECWDOG_COUNT_REG ; 
 unsigned int TICKS_TO_SECS (int,struct bcm_kona_wdt*) ; 
 int secure_register_read (struct bcm_kona_wdt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct bcm_kona_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int bcm_kona_wdt_get_timeleft(struct watchdog_device *wdog)
{
	struct bcm_kona_wdt *wdt = watchdog_get_drvdata(wdog);
	int val;
	unsigned long flags;

	spin_lock_irqsave(&wdt->lock, flags);
	val = secure_register_read(wdt, SECWDOG_COUNT_REG);
	spin_unlock_irqrestore(&wdt->lock, flags);

	if (val < 0)
		return val;

	return TICKS_TO_SECS(val & SECWDOG_COUNT_MASK, wdt);
}