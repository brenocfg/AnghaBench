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
typedef  int /*<<< orphan*/  u32 ;
struct timer_list {int dummy; } ;
struct TYPE_2__ {int timeout; } ;
struct bcm47xx_wdt {int /*<<< orphan*/  soft_timer; int /*<<< orphan*/  (* timer_set_ms ) (struct bcm47xx_wdt*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  soft_ticks; int /*<<< orphan*/  max_timer_ms; TYPE_1__ wdd; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct bcm47xx_wdt* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  soft_timer ; 
 int /*<<< orphan*/  stub1 (struct bcm47xx_wdt*,int /*<<< orphan*/ ) ; 
 struct bcm47xx_wdt* wdt ; 

__attribute__((used)) static void bcm47xx_wdt_soft_timer_tick(struct timer_list *t)
{
	struct bcm47xx_wdt *wdt = from_timer(wdt, t, soft_timer);
	u32 next_tick = min(wdt->wdd.timeout * 1000, wdt->max_timer_ms);

	if (!atomic_dec_and_test(&wdt->soft_ticks)) {
		wdt->timer_set_ms(wdt, next_tick);
		mod_timer(&wdt->soft_timer, jiffies + HZ);
	} else {
		pr_crit("Watchdog will fire soon!!!\n");
	}
}