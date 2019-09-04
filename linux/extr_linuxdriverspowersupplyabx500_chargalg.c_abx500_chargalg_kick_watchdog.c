#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int online_chg; } ;
struct abx500_chargalg {TYPE_4__* usb_chg; TYPE_2__ chg_info; TYPE_5__* ac_chg; } ;
struct TYPE_7__ {int (* kick_wd ) (TYPE_5__*) ;} ;
struct TYPE_11__ {TYPE_1__ ops; scalar_t__ external; } ;
struct TYPE_9__ {int (* kick_wd ) (TYPE_4__*) ;} ;
struct TYPE_10__ {TYPE_3__ ops; } ;

/* Variables and functions */
 int AC_CHG ; 
 int ENXIO ; 
 int USB_CHG ; 
 int stub1 (TYPE_4__*) ; 
 int stub2 (TYPE_5__*) ; 
 int stub3 (TYPE_4__*) ; 

__attribute__((used)) static int abx500_chargalg_kick_watchdog(struct abx500_chargalg *di)
{
	/* Check if charger exists and kick watchdog if charging */
	if (di->ac_chg && di->ac_chg->ops.kick_wd &&
	    di->chg_info.online_chg & AC_CHG) {
		/*
		 * If AB charger watchdog expired, pm2xxx charging
		 * gets disabled. To be safe, kick both AB charger watchdog
		 * and pm2xxx watchdog.
		 */
		if (di->ac_chg->external &&
		    di->usb_chg && di->usb_chg->ops.kick_wd)
			di->usb_chg->ops.kick_wd(di->usb_chg);

		return di->ac_chg->ops.kick_wd(di->ac_chg);
	}
	else if (di->usb_chg && di->usb_chg->ops.kick_wd &&
			di->chg_info.online_chg & USB_CHG)
		return di->usb_chg->ops.kick_wd(di->usb_chg);

	return -ENXIO;
}