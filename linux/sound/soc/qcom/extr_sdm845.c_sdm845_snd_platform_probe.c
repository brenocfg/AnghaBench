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
struct snd_soc_card {struct snd_soc_card* dai_link; struct snd_soc_card* card; struct device* dev; int /*<<< orphan*/  num_dapm_widgets; int /*<<< orphan*/  dapm_widgets; } ;
struct sdm845_snd_data {struct sdm845_snd_data* dai_link; struct sdm845_snd_data* card; struct device* dev; int /*<<< orphan*/  num_dapm_widgets; int /*<<< orphan*/  dapm_widgets; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct snd_soc_card*) ; 
 int /*<<< orphan*/  kfree (struct snd_soc_card*) ; 
 struct snd_soc_card* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qcom_snd_parse_of (struct snd_soc_card*) ; 
 int /*<<< orphan*/  sdm845_add_ops (struct snd_soc_card*) ; 
 int /*<<< orphan*/  sdm845_snd_widgets ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct snd_soc_card*) ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 

__attribute__((used)) static int sdm845_snd_platform_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card;
	struct sdm845_snd_data *data;
	struct device *dev = &pdev->dev;
	int ret;

	card = kzalloc(sizeof(*card), GFP_KERNEL);
	if (!card)
		return -ENOMEM;

	/* Allocate the private data */
	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data) {
		ret = -ENOMEM;
		goto data_alloc_fail;
	}

	card->dapm_widgets = sdm845_snd_widgets;
	card->num_dapm_widgets = ARRAY_SIZE(sdm845_snd_widgets);
	card->dev = dev;
	dev_set_drvdata(dev, card);
	ret = qcom_snd_parse_of(card);
	if (ret) {
		dev_err(dev, "Error parsing OF data\n");
		goto parse_dt_fail;
	}

	data->card = card;
	snd_soc_card_set_drvdata(card, data);

	sdm845_add_ops(card);
	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(dev, "Sound card registration failed\n");
		goto register_card_fail;
	}
	return ret;

register_card_fail:
	kfree(card->dai_link);
parse_dt_fail:
	kfree(data);
data_alloc_fail:
	kfree(card);
	return ret;
}