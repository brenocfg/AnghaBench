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
struct men_z069_drv {int /*<<< orphan*/  mem; int /*<<< orphan*/  wdt; } ;
struct mcb_device {int dummy; } ;

/* Variables and functions */
 struct men_z069_drv* mcb_get_drvdata (struct mcb_device*) ; 
 int /*<<< orphan*/  mcb_release_mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void men_z069_remove(struct mcb_device *dev)
{
	struct men_z069_drv *drv = mcb_get_drvdata(dev);

	watchdog_unregister_device(&drv->wdt);
	mcb_release_mem(drv->mem);
}