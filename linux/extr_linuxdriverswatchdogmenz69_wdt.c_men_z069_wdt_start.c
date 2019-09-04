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
typedef  int /*<<< orphan*/  u16 ;
struct watchdog_device {int dummy; } ;
struct men_z069_drv {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MEN_Z069_WTR ; 
 int /*<<< orphan*/  MEN_Z069_WTR_WDEN ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 struct men_z069_drv* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int men_z069_wdt_start(struct watchdog_device *wdt)
{
	struct men_z069_drv *drv = watchdog_get_drvdata(wdt);
	u16 val;

	val = readw(drv->base + MEN_Z069_WTR);
	val |= MEN_Z069_WTR_WDEN;
	writew(val, drv->base + MEN_Z069_WTR);

	return 0;
}