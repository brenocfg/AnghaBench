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
struct intel_sst_drv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SST_SUSPEND_DELAY ; 
 scalar_t__ acpi_disabled ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ ) ; 

void sst_configure_runtime_pm(struct intel_sst_drv *ctx)
{
	pm_runtime_set_autosuspend_delay(ctx->dev, SST_SUSPEND_DELAY);
	pm_runtime_use_autosuspend(ctx->dev);
	/*
	 * For acpi devices, the actual physical device state is
	 * initially active. So change the state to active before
	 * enabling the pm
	 */

	if (!acpi_disabled)
		pm_runtime_set_active(ctx->dev);

	pm_runtime_enable(ctx->dev);

	if (acpi_disabled)
		pm_runtime_set_active(ctx->dev);
	else
		pm_runtime_put_noidle(ctx->dev);
}