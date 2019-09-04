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
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun8i_codec_runtime_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sun8i_codec_remove(struct platform_device *pdev)
{
	pm_runtime_disable(&pdev->dev);
	if (!pm_runtime_status_suspended(&pdev->dev))
		sun8i_codec_runtime_suspend(&pdev->dev);

	return 0;
}