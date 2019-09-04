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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pll; scalar_t__ audio_pdev; } ;

/* Variables and functions */
 TYPE_1__ hdmi ; 
 int /*<<< orphan*/  hdmi_pll_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_uninit_output (struct platform_device*) ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static void hdmi5_unbind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);

	if (hdmi.audio_pdev)
		platform_device_unregister(hdmi.audio_pdev);

	hdmi_uninit_output(pdev);

	hdmi_pll_uninit(&hdmi.pll);

	pm_runtime_disable(&pdev->dev);
}