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
struct power_supply {int dummy; } ;
struct bq24190_dev_info {int /*<<< orphan*/  input_current_limit_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct bq24190_dev_info* power_supply_get_drvdata (struct power_supply*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static void bq24190_charger_external_power_changed(struct power_supply *psy)
{
	struct bq24190_dev_info *bdi = power_supply_get_drvdata(psy);

	/*
	 * The Power-Good detection may take up to 220ms, sometimes
	 * the external charger detection is quicker, and the bq24190 will
	 * reset to iinlim based on its own charger detection (which is not
	 * hooked up when using external charger detection) resulting in a
	 * too low default 500mA iinlim. Delay setting the input-current-limit
	 * for 300ms to avoid this.
	 */
	queue_delayed_work(system_wq, &bdi->input_current_limit_work,
			   msecs_to_jiffies(300));
}