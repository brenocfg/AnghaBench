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
struct snd_soc_dai_link {int num_codecs; int /*<<< orphan*/  name; scalar_t__ cpu_of_node; scalar_t__ cpu_name; int /*<<< orphan*/  cpu_dai_name; scalar_t__ platform_of_node; scalar_t__ platform_name; TYPE_1__* codecs; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dai_name; int /*<<< orphan*/  of_node; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int snd_soc_init_multicodec (struct snd_soc_card*,struct snd_soc_dai_link*) ; 

__attribute__((used)) static int soc_init_dai_link(struct snd_soc_card *card,
				   struct snd_soc_dai_link *link)
{
	int i, ret;

	ret = snd_soc_init_multicodec(card, link);
	if (ret) {
		dev_err(card->dev, "ASoC: failed to init multicodec\n");
		return ret;
	}

	for (i = 0; i < link->num_codecs; i++) {
		/*
		 * Codec must be specified by 1 of name or OF node,
		 * not both or neither.
		 */
		if (!!link->codecs[i].name ==
		    !!link->codecs[i].of_node) {
			dev_err(card->dev, "ASoC: Neither/both codec name/of_node are set for %s\n",
				link->name);
			return -EINVAL;
		}
		/* Codec DAI name must be specified */
		if (!link->codecs[i].dai_name) {
			dev_err(card->dev, "ASoC: codec_dai_name not set for %s\n",
				link->name);
			return -EINVAL;
		}
	}

	/*
	 * Platform may be specified by either name or OF node, but
	 * can be left unspecified, and a dummy platform will be used.
	 */
	if (link->platform_name && link->platform_of_node) {
		dev_err(card->dev,
			"ASoC: Both platform name/of_node are set for %s\n",
			link->name);
		return -EINVAL;
	}

	/*
	 * CPU device may be specified by either name or OF node, but
	 * can be left unspecified, and will be matched based on DAI
	 * name alone..
	 */
	if (link->cpu_name && link->cpu_of_node) {
		dev_err(card->dev,
			"ASoC: Neither/both cpu name/of_node are set for %s\n",
			link->name);
		return -EINVAL;
	}
	/*
	 * At least one of CPU DAI name or CPU device name/node must be
	 * specified
	 */
	if (!link->cpu_dai_name &&
	    !(link->cpu_name || link->cpu_of_node)) {
		dev_err(card->dev,
			"ASoC: Neither cpu_dai_name nor cpu_name/of_node are set for %s\n",
			link->name);
		return -EINVAL;
	}

	return 0;
}