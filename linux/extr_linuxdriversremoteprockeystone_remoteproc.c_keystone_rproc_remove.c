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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct keystone_rproc {int /*<<< orphan*/  rproc; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_reserved_mem_device_release (int /*<<< orphan*/ *) ; 
 struct keystone_rproc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rproc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keystone_rproc_remove(struct platform_device *pdev)
{
	struct keystone_rproc *ksproc = platform_get_drvdata(pdev);

	rproc_del(ksproc->rproc);
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	rproc_free(ksproc->rproc);
	of_reserved_mem_device_release(&pdev->dev);

	return 0;
}