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

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sirf_usp_pcm_runtime_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sirf_usp_pcm_remove(struct platform_device *pdev)
{
	if (!pm_runtime_enabled(&pdev->dev))
		sirf_usp_pcm_runtime_suspend(&pdev->dev);
	else
		pm_runtime_disable(&pdev->dev);
	return 0;
}