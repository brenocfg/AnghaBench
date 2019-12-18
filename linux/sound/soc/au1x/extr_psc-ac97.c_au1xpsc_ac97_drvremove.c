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
struct au1xpsc_audio_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CFG (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  PSC_CTRL (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  PSC_CTRL_DISABLE ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * au1xpsc_ac97_workdata ; 
 struct au1xpsc_audio_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int au1xpsc_ac97_drvremove(struct platform_device *pdev)
{
	struct au1xpsc_audio_data *wd = platform_get_drvdata(pdev);

	snd_soc_unregister_component(&pdev->dev);

	/* disable PSC completely */
	__raw_writel(0, AC97_CFG(wd));
	wmb(); /* drain writebuffer */
	__raw_writel(PSC_CTRL_DISABLE, PSC_CTRL(wd));
	wmb(); /* drain writebuffer */

	au1xpsc_ac97_workdata = NULL;	/* MDEV */

	return 0;
}