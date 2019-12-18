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
struct snd_soc_card {int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int device_property_read_u32 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,struct snd_soc_card*) ; 
 scalar_t__ dmic_wakeup_delay ; 
 struct snd_soc_card rockchip_sound_card ; 
 int rockchip_sound_of_parse_dais (int /*<<< orphan*/ *,struct snd_soc_card*) ; 

__attribute__((used)) static int rockchip_sound_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &rockchip_sound_card;
	int ret;

	ret = rockchip_sound_of_parse_dais(&pdev->dev, card);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to parse dais: %d\n", ret);
		return ret;
	}

	/* Set DMIC wakeup delay */
	ret = device_property_read_u32(&pdev->dev, "dmic-wakeup-delay-ms",
					&dmic_wakeup_delay);
	if (ret) {
		dmic_wakeup_delay = 0;
		dev_dbg(&pdev->dev,
			"no optional property 'dmic-wakeup-delay-ms' found, default: no delay\n");
	}

	card->dev = &pdev->dev;
	return devm_snd_soc_register_card(&pdev->dev, card);
}