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
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  ticks; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 TYPE_1__ bcm63xx_wdt_device ; 
 int /*<<< orphan*/  bcm63xx_wdt_hw_start () ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

__attribute__((used)) static void bcm63xx_timer_tick(struct timer_list *unused)
{
	if (!atomic_dec_and_test(&bcm63xx_wdt_device.ticks)) {
		bcm63xx_wdt_hw_start();
		mod_timer(&bcm63xx_wdt_device.timer, jiffies + HZ);
	} else
		pr_crit("watchdog will restart system\n");
}