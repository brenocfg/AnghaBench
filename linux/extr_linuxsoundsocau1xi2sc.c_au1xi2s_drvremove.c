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
 int /*<<< orphan*/  EN_D ; 
 int /*<<< orphan*/  I2S_ENABLE ; 
 int /*<<< orphan*/  WR (struct au1xpsc_audio_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct au1xpsc_audio_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int au1xi2s_drvremove(struct platform_device *pdev)
{
	struct au1xpsc_audio_data *ctx = platform_get_drvdata(pdev);

	snd_soc_unregister_component(&pdev->dev);

	WR(ctx, I2S_ENABLE, EN_D);	/* clock off, disable */

	return 0;
}