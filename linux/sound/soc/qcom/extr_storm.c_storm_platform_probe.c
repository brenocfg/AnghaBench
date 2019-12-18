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
struct snd_soc_card {int num_links; int /*<<< orphan*/ * dai_link; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct snd_soc_card* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,struct snd_soc_card*) ; 
 int snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 
 int /*<<< orphan*/  storm_dai_link ; 
 int storm_parse_of (struct snd_soc_card*) ; 

__attribute__((used)) static int storm_platform_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card;
	int ret;

	card = devm_kzalloc(&pdev->dev, sizeof(*card), GFP_KERNEL);
	if (!card)
		return -ENOMEM;

	card->dev = &pdev->dev;

	ret = snd_soc_of_parse_card_name(card, "qcom,model");
	if (ret) {
		dev_err(&pdev->dev, "error parsing card name: %d\n", ret);
		return ret;
	}

	card->dai_link	= &storm_dai_link;
	card->num_links	= 1;

	ret = storm_parse_of(card);
	if (ret) {
		dev_err(&pdev->dev, "error resolving dai links: %d\n", ret);
		return ret;
	}

	ret = devm_snd_soc_register_card(&pdev->dev, card);
	if (ret)
		dev_err(&pdev->dev, "error registering soundcard: %d\n", ret);

	return ret;

}