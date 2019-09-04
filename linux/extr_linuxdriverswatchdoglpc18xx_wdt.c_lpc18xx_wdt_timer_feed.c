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
struct watchdog_device {int timeout; } ;
struct timer_list {int dummy; } ;
struct lpc18xx_wdt_dev {int /*<<< orphan*/  timer; struct watchdog_device wdt_dev; } ;

/* Variables and functions */
 int MSEC_PER_SEC ; 
 struct lpc18xx_wdt_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 struct lpc18xx_wdt_dev* lpc18xx_wdt ; 
 int /*<<< orphan*/  lpc18xx_wdt_feed (struct watchdog_device*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void lpc18xx_wdt_timer_feed(struct timer_list *t)
{
	struct lpc18xx_wdt_dev *lpc18xx_wdt = from_timer(lpc18xx_wdt, t, timer);
	struct watchdog_device *wdt_dev = &lpc18xx_wdt->wdt_dev;

	lpc18xx_wdt_feed(wdt_dev);

	/* Use safe value (1/2 of real timeout) */
	mod_timer(&lpc18xx_wdt->timer, jiffies +
		  msecs_to_jiffies((wdt_dev->timeout * MSEC_PER_SEC) / 2));
}