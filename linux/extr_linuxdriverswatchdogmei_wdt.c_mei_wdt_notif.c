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
struct mei_wdt {scalar_t__ state; } ;
struct mei_cl_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ MEI_WDT_NOT_REQUIRED ; 
 struct mei_wdt* mei_cldev_get_drvdata (struct mei_cl_device*) ; 
 int /*<<< orphan*/  mei_wdt_register (struct mei_wdt*) ; 

__attribute__((used)) static void mei_wdt_notif(struct mei_cl_device *cldev)
{
	struct mei_wdt *wdt = mei_cldev_get_drvdata(cldev);

	if (wdt->state != MEI_WDT_NOT_REQUIRED)
		return;

	mei_wdt_register(wdt);
}