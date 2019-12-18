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
struct snd_soc_dai_link {int /*<<< orphan*/  init; int /*<<< orphan*/ * ops; TYPE_2__* codecs; TYPE_1__* cpus; int /*<<< orphan*/  dai_fmt; } ;
struct simple_dai_props {struct asoc_simple_dai* codec_dai; struct asoc_simple_dai* cpu_dai; } ;
struct link_info {int /*<<< orphan*/  dais; int /*<<< orphan*/  link; int /*<<< orphan*/  cpu; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct asoc_simple_priv {struct asoc_simple_dai* dais; } ;
struct asoc_simple_dai {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dai_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  dai_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  asoc_simple_canonicalize_cpu (struct snd_soc_dai_link*,int) ; 
 int /*<<< orphan*/  asoc_simple_canonicalize_platform (struct snd_soc_dai_link*) ; 
 int /*<<< orphan*/  asoc_simple_dai_init ; 
 int asoc_simple_parse_clk_codec (struct device*,struct device_node*,struct snd_soc_dai_link*,struct asoc_simple_dai*) ; 
 int asoc_simple_parse_clk_cpu (struct device*,struct device_node*,struct snd_soc_dai_link*,struct asoc_simple_dai*) ; 
 int asoc_simple_parse_codec (struct device_node*,struct snd_soc_dai_link*) ; 
 int asoc_simple_parse_cpu (struct device_node*,struct snd_soc_dai_link*,int*) ; 
 int asoc_simple_parse_daifmt (struct device*,struct device_node*,struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int asoc_simple_parse_tdm (struct device_node*,struct asoc_simple_dai*) ; 
 int asoc_simple_set_dailink_name (struct device*,struct snd_soc_dai_link*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct device_node*) ; 
 int /*<<< orphan*/  graph_ops ; 
 int /*<<< orphan*/  graph_parse_mclk_fs (struct device_node*,struct device_node*,struct simple_dai_props*) ; 
 struct device* simple_priv_to_dev (struct asoc_simple_priv*) ; 
 struct snd_soc_dai_link* simple_priv_to_link (struct asoc_simple_priv*,int /*<<< orphan*/ ) ; 
 struct simple_dai_props* simple_priv_to_props (struct asoc_simple_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int graph_dai_link_of(struct asoc_simple_priv *priv,
			     struct device_node *cpu_ep,
			     struct device_node *codec_ep,
			     struct link_info *li)
{
	struct device *dev = simple_priv_to_dev(priv);
	struct snd_soc_dai_link *dai_link = simple_priv_to_link(priv, li->link);
	struct simple_dai_props *dai_props = simple_priv_to_props(priv, li->link);
	struct device_node *top = dev->of_node;
	struct asoc_simple_dai *cpu_dai;
	struct asoc_simple_dai *codec_dai;
	int ret, single_cpu;

	/* Do it only CPU turn */
	if (!li->cpu)
		return 0;

	dev_dbg(dev, "link_of (%pOF)\n", cpu_ep);

	li->link++;

	cpu_dai			=
	dai_props->cpu_dai	= &priv->dais[li->dais++];
	codec_dai		=
	dai_props->codec_dai	= &priv->dais[li->dais++];

	/* Factor to mclk, used in hw_params() */
	graph_parse_mclk_fs(top, cpu_ep,   dai_props);
	graph_parse_mclk_fs(top, codec_ep, dai_props);

	ret = asoc_simple_parse_daifmt(dev, cpu_ep, codec_ep,
				       NULL, &dai_link->dai_fmt);
	if (ret < 0)
		return ret;

	ret = asoc_simple_parse_cpu(cpu_ep, dai_link, &single_cpu);
	if (ret < 0)
		return ret;

	ret = asoc_simple_parse_codec(codec_ep, dai_link);
	if (ret < 0)
		return ret;

	ret = asoc_simple_parse_tdm(cpu_ep, cpu_dai);
	if (ret < 0)
		return ret;

	ret = asoc_simple_parse_tdm(codec_ep, codec_dai);
	if (ret < 0)
		return ret;

	ret = asoc_simple_parse_clk_cpu(dev, cpu_ep, dai_link, cpu_dai);
	if (ret < 0)
		return ret;

	ret = asoc_simple_parse_clk_codec(dev, codec_ep, dai_link, codec_dai);
	if (ret < 0)
		return ret;

	ret = asoc_simple_set_dailink_name(dev, dai_link,
					   "%s-%s",
					   dai_link->cpus->dai_name,
					   dai_link->codecs->dai_name);
	if (ret < 0)
		return ret;

	dai_link->ops = &graph_ops;
	dai_link->init = asoc_simple_dai_init;

	asoc_simple_canonicalize_cpu(dai_link, single_cpu);
	asoc_simple_canonicalize_platform(dai_link);

	return 0;
}