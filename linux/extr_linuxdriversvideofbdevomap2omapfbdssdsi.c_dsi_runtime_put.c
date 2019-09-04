#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct dsi_data {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int ENOSYS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsi_runtime_put(struct platform_device *dsidev)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	int r;

	DSSDBG("dsi_runtime_put\n");

	r = pm_runtime_put_sync(&dsi->pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS);
}