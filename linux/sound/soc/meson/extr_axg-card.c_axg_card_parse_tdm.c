#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {scalar_t__ dpcm_playback; TYPE_1__* cpus; int /*<<< orphan*/  dai_fmt; int /*<<< orphan*/  init; int /*<<< orphan*/ * ops; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; struct snd_soc_dai_link* dai_link; } ;
struct device_node {int dummy; } ;
struct axg_dai_link_tdm_data {int /*<<< orphan*/  mclk_fs; } ;
struct axg_card {struct axg_dai_link_tdm_data** link_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int axg_card_add_tdm_loopback (struct snd_soc_card*,int*) ; 
 int axg_card_parse_codecs_masks (struct snd_soc_card*,struct snd_soc_dai_link*,struct device_node*,struct axg_dai_link_tdm_data*) ; 
 int axg_card_parse_cpu_tdm_slots (struct snd_soc_card*,struct snd_soc_dai_link*,struct device_node*,struct axg_dai_link_tdm_data*) ; 
 int /*<<< orphan*/  axg_card_parse_daifmt (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axg_card_tdm_be_ops ; 
 int /*<<< orphan*/  axg_card_tdm_dai_init ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct axg_dai_link_tdm_data* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct axg_card* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int axg_card_parse_tdm(struct snd_soc_card *card,
			      struct device_node *node,
			      int *index)
{
	struct axg_card *priv = snd_soc_card_get_drvdata(card);
	struct snd_soc_dai_link *link = &card->dai_link[*index];
	struct axg_dai_link_tdm_data *be;
	int ret;

	/* Allocate tdm link parameters */
	be = devm_kzalloc(card->dev, sizeof(*be), GFP_KERNEL);
	if (!be)
		return -ENOMEM;
	priv->link_data[*index] = be;

	/* Setup tdm link */
	link->ops = &axg_card_tdm_be_ops;
	link->init = axg_card_tdm_dai_init;
	link->dai_fmt = axg_card_parse_daifmt(node, link->cpus->of_node);

	of_property_read_u32(node, "mclk-fs", &be->mclk_fs);

	ret = axg_card_parse_cpu_tdm_slots(card, link, node, be);
	if (ret) {
		dev_err(card->dev, "error parsing tdm link slots\n");
		return ret;
	}

	ret = axg_card_parse_codecs_masks(card, link, node, be);
	if (ret)
		return ret;

	/* Add loopback if the pad dai has playback */
	if (link->dpcm_playback) {
		ret = axg_card_add_tdm_loopback(card, index);
		if (ret)
			return ret;
	}

	return 0;
}