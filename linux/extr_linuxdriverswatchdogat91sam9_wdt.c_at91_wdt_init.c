#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_4__ {int timeout; } ;
struct at91wdt {int mr_mask; int mr; unsigned long heartbeat; int /*<<< orphan*/  timer; TYPE_1__ wdd; scalar_t__ next_heartbeat; int /*<<< orphan*/  nowayout; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_WDT_MR ; 
 int AT91_WDT_WDD ; 
 int AT91_WDT_WDDIS ; 
 int AT91_WDT_WDFIEN ; 
 int AT91_WDT_WDV ; 
 int EINVAL ; 
 int HZ ; 
 int IRQF_IRQPOLL ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_SHARED ; 
 int WDT_MR_RESET ; 
 int /*<<< orphan*/  at91_ping ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  heartbeat ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct at91wdt*) ; 
 unsigned long ticks_to_hz_rounddown (int) ; 
 unsigned long ticks_to_hz_roundup (int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_interrupt ; 
 int wdt_read (struct at91wdt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_write (struct at91wdt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int at91_wdt_init(struct platform_device *pdev, struct at91wdt *wdt)
{
	u32 tmp;
	u32 delta;
	u32 value;
	int err;
	u32 mask = wdt->mr_mask;
	unsigned long min_heartbeat = 1;
	unsigned long max_heartbeat;
	struct device *dev = &pdev->dev;

	tmp = wdt_read(wdt, AT91_WDT_MR);
	if ((tmp & mask) != (wdt->mr & mask)) {
		if (tmp == WDT_MR_RESET) {
			wdt_write(wdt, AT91_WDT_MR, wdt->mr);
			tmp = wdt_read(wdt, AT91_WDT_MR);
		}
	}

	if (tmp & AT91_WDT_WDDIS) {
		if (wdt->mr & AT91_WDT_WDDIS)
			return 0;
		dev_err(dev, "watchdog is disabled\n");
		return -EINVAL;
	}

	value = tmp & AT91_WDT_WDV;
	delta = (tmp & AT91_WDT_WDD) >> 16;

	if (delta < value)
		min_heartbeat = ticks_to_hz_roundup(value - delta);

	max_heartbeat = ticks_to_hz_rounddown(value);
	if (!max_heartbeat) {
		dev_err(dev,
			"heartbeat is too small for the system to handle it correctly\n");
		return -EINVAL;
	}

	/*
	 * Try to reset the watchdog counter 4 or 2 times more often than
	 * actually requested, to avoid spurious watchdog reset.
	 * If this is not possible because of the min_heartbeat value, reset
	 * it at the min_heartbeat period.
	 */
	if ((max_heartbeat / 4) >= min_heartbeat)
		wdt->heartbeat = max_heartbeat / 4;
	else if ((max_heartbeat / 2) >= min_heartbeat)
		wdt->heartbeat = max_heartbeat / 2;
	else
		wdt->heartbeat = min_heartbeat;

	if (max_heartbeat < min_heartbeat + 4)
		dev_warn(dev,
			 "min heartbeat and max heartbeat might be too close for the system to handle it correctly\n");

	if ((tmp & AT91_WDT_WDFIEN) && wdt->irq) {
		err = request_irq(wdt->irq, wdt_interrupt,
				  IRQF_SHARED | IRQF_IRQPOLL |
				  IRQF_NO_SUSPEND,
				  pdev->name, wdt);
		if (err)
			return err;
	}

	if ((tmp & wdt->mr_mask) != (wdt->mr & wdt->mr_mask))
		dev_warn(dev,
			 "watchdog already configured differently (mr = %x expecting %x)\n",
			 tmp & wdt->mr_mask, wdt->mr & wdt->mr_mask);

	timer_setup(&wdt->timer, at91_ping, 0);

	/*
	 * Use min_heartbeat the first time to avoid spurious watchdog reset:
	 * we don't know for how long the watchdog counter is running, and
	 *  - resetting it right now might trigger a watchdog fault reset
	 *  - waiting for heartbeat time might lead to a watchdog timeout
	 *    reset
	 */
	mod_timer(&wdt->timer, jiffies + min_heartbeat);

	/* Try to set timeout from device tree first */
	if (watchdog_init_timeout(&wdt->wdd, 0, dev))
		watchdog_init_timeout(&wdt->wdd, heartbeat, dev);
	watchdog_set_nowayout(&wdt->wdd, wdt->nowayout);
	err = watchdog_register_device(&wdt->wdd);
	if (err)
		goto out_stop_timer;

	wdt->next_heartbeat = jiffies + wdt->wdd.timeout * HZ;

	return 0;

out_stop_timer:
	del_timer(&wdt->timer);
	return err;
}