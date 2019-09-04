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
struct snd_soc_dai_link {int /*<<< orphan*/  cpu_of_node; int /*<<< orphan*/  init; int /*<<< orphan*/ * ops; int /*<<< orphan*/  codec_dai_name; int /*<<< orphan*/  cpu_dai_name; int /*<<< orphan*/  dai_fmt; } ;
struct asoc_simple_dai {int dummy; } ;
struct graph_dai_props {int /*<<< orphan*/  mclk_fs; struct asoc_simple_dai codec_dai; struct asoc_simple_dai cpu_dai; } ;
struct graph_card_data {int dummy; } ;
struct device_node {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  asoc_graph_card_dai_init ; 
 int /*<<< orphan*/  asoc_graph_card_ops ; 
 int /*<<< orphan*/  asoc_simple_card_canonicalize_cpu (struct snd_soc_dai_link*,int) ; 
 int asoc_simple_card_canonicalize_dailink (struct snd_soc_dai_link*) ; 
 int asoc_simple_card_of_parse_tdm (struct device_node*,struct asoc_simple_dai*) ; 
 int asoc_simple_card_parse_clk_codec (struct device*,struct device_node*,struct snd_soc_dai_link*,struct asoc_simple_dai*) ; 
 int asoc_simple_card_parse_clk_cpu (struct device*,struct device_node*,struct snd_soc_dai_link*,struct asoc_simple_dai*) ; 
 int asoc_simple_card_parse_daifmt (struct device*,struct device_node*,struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int asoc_simple_card_parse_graph_codec (struct device_node*,struct snd_soc_dai_link*) ; 
 int asoc_simple_card_parse_graph_cpu (struct device_node*,struct snd_soc_dai_link*) ; 
 int asoc_simple_card_set_dailink_name (struct device*,struct snd_soc_dai_link*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* graph_priv_to_dev (struct graph_card_data*) ; 
 struct snd_soc_dai_link* graph_priv_to_link (struct graph_card_data*,int) ; 
 struct graph_dai_props* graph_priv_to_props (struct graph_card_data*,int) ; 
 struct device_node* of_get_next_child (struct device_node*,int /*<<< orphan*/ *) ; 
 int of_graph_get_endpoint_count (int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_remote_endpoint (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asoc_graph_card_dai_link_of(struct device_node *cpu_port,
					struct graph_card_data *priv,
					int idx)
{
	struct device *dev = graph_priv_to_dev(priv);
	struct snd_soc_dai_link *dai_link = graph_priv_to_link(priv, idx);
	struct graph_dai_props *dai_props = graph_priv_to_props(priv, idx);
	struct asoc_simple_dai *cpu_dai = &dai_props->cpu_dai;
	struct asoc_simple_dai *codec_dai = &dai_props->codec_dai;
	struct device_node *cpu_ep    = of_get_next_child(cpu_port, NULL);
	struct device_node *codec_ep = of_graph_get_remote_endpoint(cpu_ep);
	struct device_node *rcpu_ep = of_graph_get_remote_endpoint(codec_ep);
	int ret;

	if (rcpu_ep != cpu_ep) {
		dev_err(dev, "remote-endpoint mismatch (%s/%s/%s)\n",
			cpu_ep->name, codec_ep->name, rcpu_ep->name);
		ret = -EINVAL;
		goto dai_link_of_err;
	}

	ret = asoc_simple_card_parse_daifmt(dev, cpu_ep, codec_ep,
					    NULL, &dai_link->dai_fmt);
	if (ret < 0)
		goto dai_link_of_err;

	of_property_read_u32(rcpu_ep, "mclk-fs", &dai_props->mclk_fs);

	ret = asoc_simple_card_parse_graph_cpu(cpu_ep, dai_link);
	if (ret < 0)
		goto dai_link_of_err;

	ret = asoc_simple_card_parse_graph_codec(codec_ep, dai_link);
	if (ret < 0)
		goto dai_link_of_err;

	ret = asoc_simple_card_of_parse_tdm(cpu_ep, cpu_dai);
	if (ret < 0)
		goto dai_link_of_err;

	ret = asoc_simple_card_of_parse_tdm(codec_ep, codec_dai);
	if (ret < 0)
		goto dai_link_of_err;

	ret = asoc_simple_card_parse_clk_cpu(dev, cpu_ep, dai_link, cpu_dai);
	if (ret < 0)
		goto dai_link_of_err;

	ret = asoc_simple_card_parse_clk_codec(dev, codec_ep, dai_link, codec_dai);
	if (ret < 0)
		goto dai_link_of_err;

	ret = asoc_simple_card_canonicalize_dailink(dai_link);
	if (ret < 0)
		goto dai_link_of_err;

	ret = asoc_simple_card_set_dailink_name(dev, dai_link,
						"%s-%s",
						dai_link->cpu_dai_name,
						dai_link->codec_dai_name);
	if (ret < 0)
		goto dai_link_of_err;

	dai_link->ops = &asoc_graph_card_ops;
	dai_link->init = asoc_graph_card_dai_init;

	asoc_simple_card_canonicalize_cpu(dai_link,
		of_graph_get_endpoint_count(dai_link->cpu_of_node) == 1);

dai_link_of_err:
	of_node_put(cpu_ep);
	of_node_put(rcpu_ep);
	of_node_put(codec_ep);

	return ret;
}