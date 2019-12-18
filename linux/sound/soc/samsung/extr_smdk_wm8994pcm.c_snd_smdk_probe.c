#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__ smdk_pcm ; 

__attribute__((used)) static int snd_smdk_probe(struct platform_device *pdev)
{
	int ret = 0;

	smdk_pcm.dev = &pdev->dev;
	ret = devm_snd_soc_register_card(&pdev->dev, &smdk_pcm);
	if (ret)
		dev_err(&pdev->dev, "snd_soc_register_card failed %d\n", ret);

	return ret;
}