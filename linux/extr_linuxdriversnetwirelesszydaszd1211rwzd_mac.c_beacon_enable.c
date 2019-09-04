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
struct TYPE_2__ {int /*<<< orphan*/  watchdog_work; int /*<<< orphan*/  last_update; } ;
struct zd_mac {TYPE_1__ beacon; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEACON_WATCHDOG_DELAY ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_mac_dev (struct zd_mac*) ; 
 int /*<<< orphan*/  zd_workqueue ; 

__attribute__((used)) static void beacon_enable(struct zd_mac *mac)
{
	dev_dbg_f(zd_mac_dev(mac), "\n");

	mac->beacon.last_update = jiffies;
	queue_delayed_work(zd_workqueue, &mac->beacon.watchdog_work,
			   BEACON_WATCHDOG_DELAY);
}