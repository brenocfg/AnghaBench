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
struct au1xpsc_audio_dmadata {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  au1xpsc_soc_component ; 
 struct au1xpsc_audio_dmadata* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct au1xpsc_audio_dmadata*) ; 

__attribute__((used)) static int au1xpsc_pcm_drvprobe(struct platform_device *pdev)
{
	struct au1xpsc_audio_dmadata *dmadata;

	dmadata = devm_kcalloc(&pdev->dev,
			       2, sizeof(struct au1xpsc_audio_dmadata),
			       GFP_KERNEL);
	if (!dmadata)
		return -ENOMEM;

	platform_set_drvdata(pdev, dmadata);

	return devm_snd_soc_register_component(&pdev->dev,
					&au1xpsc_soc_component, NULL, 0);
}