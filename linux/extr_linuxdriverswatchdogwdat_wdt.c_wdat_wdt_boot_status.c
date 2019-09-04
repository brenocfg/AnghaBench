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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  bootstatus; } ;
struct wdat_wdt {TYPE_2__* pdev; TYPE_1__ wdd; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_WDAT_GET_STATUS ; 
 int /*<<< orphan*/  ACPI_WDAT_SET_STATUS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int wdat_wdt_run_action (struct wdat_wdt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void wdat_wdt_boot_status(struct wdat_wdt *wdat)
{
	u32 boot_status = 0;
	int ret;

	ret = wdat_wdt_run_action(wdat, ACPI_WDAT_GET_STATUS, 0, &boot_status);
	if (ret && ret != -EOPNOTSUPP) {
		dev_err(&wdat->pdev->dev, "Failed to read boot status\n");
		return;
	}

	if (boot_status)
		wdat->wdd.bootstatus = WDIOF_CARDRESET;

	/* Clear the boot status in case BIOS did not do it */
	ret = wdat_wdt_run_action(wdat, ACPI_WDAT_SET_STATUS, 0, NULL);
	if (ret && ret != -EOPNOTSUPP)
		dev_err(&wdat->pdev->dev, "Failed to clear boot status\n");
}