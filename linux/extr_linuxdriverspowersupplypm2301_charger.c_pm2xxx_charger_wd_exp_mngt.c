#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  psy; } ;
struct TYPE_3__ {int wd_expired; } ;
struct pm2xxx_charger {TYPE_2__ ac_chg; TYPE_1__ ac; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm2xxx_charger_wd_exp_mngt(struct pm2xxx_charger *pm2, int val)
{
	dev_dbg(pm2->dev , "20 minutes watchdog expired\n");

	pm2->ac.wd_expired = true;
	power_supply_changed(pm2->ac_chg.psy);

	return 0;
}