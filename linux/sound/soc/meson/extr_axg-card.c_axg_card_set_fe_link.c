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
struct snd_soc_dai_link_component {char* dai_name; char* name; } ;
struct snd_soc_dai_link {int num_codecs; int dynamic; int dpcm_merged_format; int dpcm_merged_chan; int dpcm_merged_rate; int dpcm_playback; int dpcm_capture; struct snd_soc_dai_link_component* codecs; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int axg_card_set_link_name (struct snd_soc_card*,struct snd_soc_dai_link*,struct device_node*,char*) ; 
 struct snd_soc_dai_link_component* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axg_card_set_fe_link(struct snd_soc_card *card,
				struct snd_soc_dai_link *link,
				struct device_node *node,
				bool is_playback)
{
	struct snd_soc_dai_link_component *codec;

	codec = devm_kzalloc(card->dev, sizeof(*codec), GFP_KERNEL);
	if (!codec)
		return -ENOMEM;

	link->codecs = codec;
	link->num_codecs = 1;

	link->dynamic = 1;
	link->dpcm_merged_format = 1;
	link->dpcm_merged_chan = 1;
	link->dpcm_merged_rate = 1;
	link->codecs->dai_name = "snd-soc-dummy-dai";
	link->codecs->name = "snd-soc-dummy";

	if (is_playback)
		link->dpcm_playback = 1;
	else
		link->dpcm_capture = 1;

	return axg_card_set_link_name(card, link, node, "fe");
}