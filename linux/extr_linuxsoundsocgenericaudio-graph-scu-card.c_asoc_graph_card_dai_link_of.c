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
struct snd_soc_dai_link {char* codec_dai_name; char* codec_name; int dynamic; int dpcm_merged_format; char* cpu_dai_name; char* cpu_name; int no_pcm; unsigned int dai_fmt; int dpcm_playback; int dpcm_capture; int /*<<< orphan*/  init; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * codec_of_node; int /*<<< orphan*/  be_hw_params_fixup; int /*<<< orphan*/ * cpu_of_node; } ;
struct snd_soc_card {int dummy; } ;
struct graph_card_data {int /*<<< orphan*/  codec_conf; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct asoc_simple_dai {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asoc_graph_card_be_hw_params_fixup ; 
 int /*<<< orphan*/  asoc_graph_card_dai_init ; 
 int /*<<< orphan*/  asoc_graph_card_ops ; 
 int /*<<< orphan*/  asoc_simple_card_canonicalize_cpu (struct snd_soc_dai_link*,int) ; 
 int asoc_simple_card_canonicalize_dailink (struct snd_soc_dai_link*) ; 
 int asoc_simple_card_of_parse_tdm (struct device_node*,struct asoc_simple_dai*) ; 
 int asoc_simple_card_parse_clk_codec (struct device*,struct device_node*,struct snd_soc_dai_link*,struct asoc_simple_dai*) ; 
 int asoc_simple_card_parse_clk_cpu (struct device*,struct device_node*,struct snd_soc_dai_link*,struct asoc_simple_dai*) ; 
 int asoc_simple_card_parse_graph_codec (struct device_node*,struct snd_soc_dai_link*) ; 
 int asoc_simple_card_parse_graph_cpu (struct device_node*,struct snd_soc_dai_link*) ; 
 int asoc_simple_card_set_dailink_name (struct device*,struct snd_soc_dai_link*,char*,char*) ; 
 struct snd_soc_card* graph_priv_to_card (struct graph_card_data*) ; 
 struct device* graph_priv_to_dev (struct graph_card_data*) ; 
 struct snd_soc_dai_link* graph_priv_to_link (struct graph_card_data*,int) ; 
 struct asoc_simple_dai* graph_priv_to_props (struct graph_card_data*,int) ; 
 int of_graph_get_endpoint_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_of_parse_audio_prefix (struct snd_soc_card*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int asoc_graph_card_dai_link_of(struct device_node *ep,
				       struct graph_card_data *priv,
				       unsigned int daifmt,
				       int idx, int is_fe)
{
	struct device *dev = graph_priv_to_dev(priv);
	struct snd_soc_dai_link *dai_link = graph_priv_to_link(priv, idx);
	struct asoc_simple_dai *dai_props = graph_priv_to_props(priv, idx);
	struct snd_soc_card *card = graph_priv_to_card(priv);
	int ret;

	if (is_fe) {
		/* BE is dummy */
		dai_link->codec_of_node		= NULL;
		dai_link->codec_dai_name	= "snd-soc-dummy-dai";
		dai_link->codec_name		= "snd-soc-dummy";

		/* FE settings */
		dai_link->dynamic		= 1;
		dai_link->dpcm_merged_format	= 1;

		ret = asoc_simple_card_parse_graph_cpu(ep, dai_link);
		if (ret)
			return ret;

		ret = asoc_simple_card_parse_clk_cpu(dev, ep, dai_link, dai_props);
		if (ret < 0)
			return ret;

		ret = asoc_simple_card_set_dailink_name(dev, dai_link,
							"fe.%s",
							dai_link->cpu_dai_name);
		if (ret < 0)
			return ret;

		/* card->num_links includes Codec */
		asoc_simple_card_canonicalize_cpu(dai_link,
			of_graph_get_endpoint_count(dai_link->cpu_of_node) == 1);
	} else {
		/* FE is dummy */
		dai_link->cpu_of_node		= NULL;
		dai_link->cpu_dai_name		= "snd-soc-dummy-dai";
		dai_link->cpu_name		= "snd-soc-dummy";

		/* BE settings */
		dai_link->no_pcm		= 1;
		dai_link->be_hw_params_fixup	= asoc_graph_card_be_hw_params_fixup;

		ret = asoc_simple_card_parse_graph_codec(ep, dai_link);
		if (ret < 0)
			return ret;

		ret = asoc_simple_card_parse_clk_codec(dev, ep, dai_link, dai_props);
		if (ret < 0)
			return ret;

		ret = asoc_simple_card_set_dailink_name(dev, dai_link,
							"be.%s",
							dai_link->codec_dai_name);
		if (ret < 0)
			return ret;

		snd_soc_of_parse_audio_prefix(card,
					      &priv->codec_conf,
					      dai_link->codec_of_node,
					      "prefix");
	}

	ret = asoc_simple_card_of_parse_tdm(ep, dai_props);
	if (ret)
		return ret;

	ret = asoc_simple_card_canonicalize_dailink(dai_link);
	if (ret < 0)
		return ret;

	dai_link->dai_fmt		= daifmt;
	dai_link->dpcm_playback		= 1;
	dai_link->dpcm_capture		= 1;
	dai_link->ops			= &asoc_graph_card_ops;
	dai_link->init			= asoc_graph_card_dai_init;

	return 0;
}