#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  platform; } ;
struct snd_soc_acpi_mach {TYPE_1__ mach_params; } ;
struct TYPE_8__ {struct snd_soc_acpi_mach* platform_data; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_7__ {TYPE_4__* dev; } ;

/* Variables and functions */
 int devm_snd_soc_register_card (TYPE_4__*,TYPE_2__*) ; 
 TYPE_2__ haswell_rt5640 ; 
 int snd_soc_fixup_dai_links_platform_name (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int haswell_audio_probe(struct platform_device *pdev)
{
	struct snd_soc_acpi_mach *mach;
	int ret;

	haswell_rt5640.dev = &pdev->dev;

	/* override plaform name, if required */
	mach = (&pdev->dev)->platform_data;
	ret = snd_soc_fixup_dai_links_platform_name(&haswell_rt5640,
						    mach->mach_params.platform);
	if (ret)
		return ret;

	return devm_snd_soc_register_card(&pdev->dev, &haswell_rt5640);
}