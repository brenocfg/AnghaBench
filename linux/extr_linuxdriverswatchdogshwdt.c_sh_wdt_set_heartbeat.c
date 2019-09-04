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
struct watchdog_device {unsigned int timeout; } ;
struct sh_wdt {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int heartbeat ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 struct sh_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int sh_wdt_set_heartbeat(struct watchdog_device *wdt_dev, unsigned t)
{
	struct sh_wdt *wdt = watchdog_get_drvdata(wdt_dev);
	unsigned long flags;

	if (unlikely(t < 1 || t > 3600)) /* arbitrary upper limit */
		return -EINVAL;

	spin_lock_irqsave(&wdt->lock, flags);
	heartbeat = t;
	wdt_dev->timeout = t;
	spin_unlock_irqrestore(&wdt->lock, flags);

	return 0;
}