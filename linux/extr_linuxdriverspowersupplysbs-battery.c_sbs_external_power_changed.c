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
struct sbs_info {int /*<<< orphan*/  poll_retry_count; int /*<<< orphan*/  poll_time; int /*<<< orphan*/  work; } ;
struct power_supply {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct sbs_info* power_supply_get_drvdata (struct power_supply*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sbs_external_power_changed(struct power_supply *psy)
{
	struct sbs_info *chip = power_supply_get_drvdata(psy);

	/* cancel outstanding work */
	cancel_delayed_work_sync(&chip->work);

	schedule_delayed_work(&chip->work, HZ);
	chip->poll_time = chip->poll_retry_count;
}