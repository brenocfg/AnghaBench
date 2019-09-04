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
struct watchdog_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* variant; } ;
struct TYPE_3__ {int (* configure ) (struct watchdog_device*,int) ;} ;

/* Variables and functions */
 int stub1 (struct watchdog_device*,int) ; 
 TYPE_2__* to_rave_sp_wdt (struct watchdog_device*) ; 

__attribute__((used)) static int rave_sp_wdt_configure(struct watchdog_device *wdd, bool on)
{
	return to_rave_sp_wdt(wdd)->variant->configure(wdd, on);
}