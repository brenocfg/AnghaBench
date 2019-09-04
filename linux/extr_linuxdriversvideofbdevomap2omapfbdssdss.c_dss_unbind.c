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
struct TYPE_2__ {scalar_t__ video2_pll; scalar_t__ video1_pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_unbind_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ dss ; 
 int dss_initialized ; 
 int /*<<< orphan*/  dss_put_clocks () ; 
 int /*<<< orphan*/  dss_uninit_ports (struct platform_device*) ; 
 int /*<<< orphan*/  dss_video_pll_uninit (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static void dss_unbind(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);

	dss_initialized = false;

	component_unbind_all(&pdev->dev, NULL);

	if (dss.video1_pll)
		dss_video_pll_uninit(dss.video1_pll);

	if (dss.video2_pll)
		dss_video_pll_uninit(dss.video2_pll);

	dss_uninit_ports(pdev);

	pm_runtime_disable(&pdev->dev);

	dss_put_clocks();
}