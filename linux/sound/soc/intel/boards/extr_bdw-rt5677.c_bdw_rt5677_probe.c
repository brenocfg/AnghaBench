#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  platform; } ;
struct snd_soc_acpi_mach {TYPE_1__ mach_params; } ;
struct TYPE_11__ {struct snd_soc_acpi_mach* platform_data; } ;
struct platform_device {TYPE_4__ dev; } ;
struct bdw_rt5677_priv {int dummy; } ;
struct TYPE_10__ {TYPE_4__* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__ bdw_rt5677_card ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 struct bdw_rt5677_priv* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_2__*,struct bdw_rt5677_priv*) ; 
 int snd_soc_fixup_dai_links_platform_name (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bdw_rt5677_probe(struct platform_device *pdev)
{
	struct bdw_rt5677_priv *bdw_rt5677;
	struct snd_soc_acpi_mach *mach;
	int ret;

	bdw_rt5677_card.dev = &pdev->dev;

	/* Allocate driver private struct */
	bdw_rt5677 = devm_kzalloc(&pdev->dev, sizeof(struct bdw_rt5677_priv),
		GFP_KERNEL);
	if (!bdw_rt5677) {
		dev_err(&pdev->dev, "Can't allocate bdw_rt5677\n");
		return -ENOMEM;
	}

	/* override plaform name, if required */
	mach = (&pdev->dev)->platform_data;
	ret = snd_soc_fixup_dai_links_platform_name(&bdw_rt5677_card,
						    mach->mach_params.platform);
	if (ret)
		return ret;

	snd_soc_card_set_drvdata(&bdw_rt5677_card, bdw_rt5677);

	return devm_snd_soc_register_card(&pdev->dev, &bdw_rt5677_card);
}