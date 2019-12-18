#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link_component {char* dai_name; struct device_node* of_node; } ;
struct snd_soc_dai_link {int num_cpus; int num_codecs; int num_platforms; char* name; char* stream_name; unsigned int dai_fmt; struct snd_soc_dai_link_component* platforms; struct snd_soc_dai_link_component* cpus; struct snd_soc_dai_link_component* codecs; int /*<<< orphan*/ * init; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {int num_links; struct snd_soc_dai_link* dai_link; TYPE_4__* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int SND_SOC_DAIFMT_CBM_CFM ; 
 unsigned int SND_SOC_DAIFMT_CBS_CFS ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 void* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ snd_proto ; 
 int /*<<< orphan*/  snd_proto_init ; 
 int snd_soc_of_parse_card_name (TYPE_1__*,char*) ; 
 unsigned int snd_soc_of_parse_daifmt (struct device_node*,int /*<<< orphan*/ *,struct device_node**,struct device_node**) ; 
 int snd_soc_register_card (TYPE_1__*) ; 

__attribute__((used)) static int snd_proto_probe(struct platform_device *pdev)
{
	struct snd_soc_dai_link *dai;
	struct snd_soc_dai_link_component *comp;
	struct device_node *np = pdev->dev.of_node;
	struct device_node *codec_np, *cpu_np;
	struct device_node *bitclkmaster = NULL;
	struct device_node *framemaster = NULL;
	unsigned int dai_fmt;
	int ret = 0;

	if (!np) {
		dev_err(&pdev->dev, "No device node supplied\n");
		return -EINVAL;
	}

	snd_proto.dev = &pdev->dev;
	ret = snd_soc_of_parse_card_name(&snd_proto, "model");
	if (ret)
		return ret;

	dai = devm_kzalloc(&pdev->dev, sizeof(*dai), GFP_KERNEL);
	if (!dai)
		return -ENOMEM;

	/* for cpus/codecs/platforms */
	comp = devm_kzalloc(&pdev->dev, 3 * sizeof(*comp), GFP_KERNEL);
	if (!comp)
		return -ENOMEM;

	snd_proto.dai_link = dai;
	snd_proto.num_links = 1;

	dai->cpus = &comp[0];
	dai->num_cpus = 1;
	dai->codecs = &comp[1];
	dai->num_codecs = 1;
	dai->platforms = &comp[2];
	dai->num_platforms = 1;

	dai->name = "WM8731";
	dai->stream_name = "WM8731 HiFi";
	dai->codecs->dai_name = "wm8731-hifi";
	dai->init = &snd_proto_init;

	codec_np = of_parse_phandle(np, "audio-codec", 0);
	if (!codec_np) {
		dev_err(&pdev->dev, "audio-codec node missing\n");
		return -EINVAL;
	}
	dai->codecs->of_node = codec_np;

	cpu_np = of_parse_phandle(np, "i2s-controller", 0);
	if (!cpu_np) {
		dev_err(&pdev->dev, "i2s-controller missing\n");
		return -EINVAL;
	}
	dai->cpus->of_node = cpu_np;
	dai->platforms->of_node = cpu_np;

	dai_fmt = snd_soc_of_parse_daifmt(np, NULL,
					  &bitclkmaster, &framemaster);
	if (bitclkmaster != framemaster) {
		dev_err(&pdev->dev, "Must be the same bitclock and frame master\n");
		return -EINVAL;
	}
	if (bitclkmaster) {
		dai_fmt &= ~SND_SOC_DAIFMT_MASTER_MASK;
		if (codec_np == bitclkmaster)
			dai_fmt |= SND_SOC_DAIFMT_CBM_CFM;
		else
			dai_fmt |= SND_SOC_DAIFMT_CBS_CFS;
	}
	of_node_put(bitclkmaster);
	of_node_put(framemaster);
	dai->dai_fmt = dai_fmt;

	of_node_put(codec_np);
	of_node_put(cpu_np);

	ret = snd_soc_register_card(&snd_proto);
	if (ret && ret != -EPROBE_DEFER)
		dev_err(&pdev->dev,
			"snd_soc_register_card() failed: %d\n", ret);

	return ret;
}