#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_7__ {struct device* dev; int /*<<< orphan*/  owner; } ;
struct axg_card {TYPE_1__ card; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int axg_card_add_aux_devices (TYPE_1__*) ; 
 int axg_card_add_links (TYPE_1__*) ; 
 int /*<<< orphan*/  axg_card_clean_references (struct axg_card*) ; 
 int axg_card_parse_of_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct axg_card* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct axg_card*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_1__*,struct axg_card*) ; 
 int /*<<< orphan*/  snd_soc_of_parse_audio_routing ; 
 int /*<<< orphan*/  snd_soc_of_parse_audio_simple_widgets ; 
 int snd_soc_of_parse_card_name (TYPE_1__*,char*) ; 

__attribute__((used)) static int axg_card_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct axg_card *priv;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);
	snd_soc_card_set_drvdata(&priv->card, priv);

	priv->card.owner = THIS_MODULE;
	priv->card.dev = dev;

	ret = snd_soc_of_parse_card_name(&priv->card, "model");
	if (ret < 0)
		return ret;

	ret = axg_card_parse_of_optional(&priv->card, "audio-routing",
					 snd_soc_of_parse_audio_routing);
	if (ret) {
		dev_err(dev, "error while parsing routing\n");
		return ret;
	}

	ret = axg_card_parse_of_optional(&priv->card, "audio-widgets",
					 snd_soc_of_parse_audio_simple_widgets);
	if (ret) {
		dev_err(dev, "error while parsing widgets\n");
		return ret;
	}

	ret = axg_card_add_links(&priv->card);
	if (ret)
		goto out_err;

	ret = axg_card_add_aux_devices(&priv->card);
	if (ret)
		goto out_err;

	ret = devm_snd_soc_register_card(dev, &priv->card);
	if (ret)
		goto out_err;

	return 0;

out_err:
	axg_card_clean_references(priv);
	return ret;
}