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
struct sta32x_priv {int /*<<< orphan*/  watchdog_work; scalar_t__ shutdown; TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ needs_esd_watchdog; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static void sta32x_watchdog_start(struct sta32x_priv *sta32x)
{
	if (sta32x->pdata->needs_esd_watchdog) {
		sta32x->shutdown = 0;
		queue_delayed_work(system_power_efficient_wq,
				   &sta32x->watchdog_work,
				   round_jiffies_relative(HZ));
	}
}