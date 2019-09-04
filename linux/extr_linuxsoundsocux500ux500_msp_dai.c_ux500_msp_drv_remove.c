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
struct ux500_msp_i2s_drvdata {int /*<<< orphan*/  msp; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRCMU_QOS_APE_OPP ; 
 struct ux500_msp_i2s_drvdata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prcmu_qos_remove_requirement (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ux500_msp_i2s_cleanup_msp (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ux500_pcm_unregister_platform (struct platform_device*) ; 

__attribute__((used)) static int ux500_msp_drv_remove(struct platform_device *pdev)
{
	struct ux500_msp_i2s_drvdata *drvdata = dev_get_drvdata(&pdev->dev);

	ux500_pcm_unregister_platform(pdev);

	snd_soc_unregister_component(&pdev->dev);

	prcmu_qos_remove_requirement(PRCMU_QOS_APE_OPP, "ux500_msp_i2s");

	ux500_msp_i2s_cleanup_msp(pdev, drvdata->msp);

	return 0;
}