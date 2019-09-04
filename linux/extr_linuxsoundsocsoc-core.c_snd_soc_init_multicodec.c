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
struct snd_soc_dai_link_component {int dummy; } ;
struct snd_soc_dai_link {int num_codecs; TYPE_1__* codecs; scalar_t__ codec_dai_name; scalar_t__ codec_of_node; scalar_t__ codec_name; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ dai_name; scalar_t__ of_node; scalar_t__ name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_soc_init_multicodec(struct snd_soc_card *card,
				   struct snd_soc_dai_link *dai_link)
{
	/* Legacy codec/codec_dai link is a single entry in multicodec */
	if (dai_link->codec_name || dai_link->codec_of_node ||
	    dai_link->codec_dai_name) {
		dai_link->num_codecs = 1;

		dai_link->codecs = devm_kzalloc(card->dev,
				sizeof(struct snd_soc_dai_link_component),
				GFP_KERNEL);
		if (!dai_link->codecs)
			return -ENOMEM;

		dai_link->codecs[0].name = dai_link->codec_name;
		dai_link->codecs[0].of_node = dai_link->codec_of_node;
		dai_link->codecs[0].dai_name = dai_link->codec_dai_name;
	}

	if (!dai_link->codecs) {
		dev_err(card->dev, "ASoC: DAI link has no CODECs\n");
		return -EINVAL;
	}

	return 0;
}