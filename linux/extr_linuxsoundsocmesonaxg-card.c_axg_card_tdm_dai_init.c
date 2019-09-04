#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {size_t num; int num_codecs; TYPE_2__* cpu_dai; struct snd_soc_dai** codec_dais; int /*<<< orphan*/  card; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct axg_dai_link_tdm_data {int /*<<< orphan*/  slot_width; int /*<<< orphan*/  slots; int /*<<< orphan*/  rx_mask; int /*<<< orphan*/  tx_mask; TYPE_1__* codec_masks; } ;
struct axg_card {scalar_t__* link_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int axg_tdm_set_tdm_slots (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct axg_card* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_tdm_slot (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axg_card_tdm_dai_init(struct snd_soc_pcm_runtime *rtd)
{
	struct axg_card *priv = snd_soc_card_get_drvdata(rtd->card);
	struct axg_dai_link_tdm_data *be =
		(struct axg_dai_link_tdm_data *)priv->link_data[rtd->num];
	struct snd_soc_dai *codec_dai;
	int ret, i;

	for (i = 0; i < rtd->num_codecs; i++) {
		codec_dai = rtd->codec_dais[i];
		ret = snd_soc_dai_set_tdm_slot(codec_dai,
					       be->codec_masks[i].tx,
					       be->codec_masks[i].rx,
					       be->slots, be->slot_width);
		if (ret && ret != -ENOTSUPP) {
			dev_err(codec_dai->dev,
				"setting tdm link slots failed\n");
			return ret;
		}
	}

	ret = axg_tdm_set_tdm_slots(rtd->cpu_dai, be->tx_mask, be->rx_mask,
				    be->slots, be->slot_width);
	if (ret) {
		dev_err(rtd->cpu_dai->dev, "setting tdm link slots failed\n");
		return ret;
	}

	return 0;
}