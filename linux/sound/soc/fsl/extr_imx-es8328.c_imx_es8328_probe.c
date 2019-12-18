#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct snd_soc_dai_link_component {char* dai_name; struct device_node* of_node; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {int num_links; TYPE_1__* dai_link; int /*<<< orphan*/  owner; int /*<<< orphan*/  num_dapm_widgets; int /*<<< orphan*/  dapm_widgets; struct device* dev; } ;
struct TYPE_5__ {int num_cpus; int num_codecs; int num_platforms; char* name; char* stream_name; int dai_fmt; int /*<<< orphan*/ * init; struct snd_soc_dai_link_component* platforms; struct snd_soc_dai_link_component* cpus; struct snd_soc_dai_link_component* codecs; } ;
struct imx_es8328_data {TYPE_2__ card; TYPE_1__ dai; int /*<<< orphan*/  jack_gpio; struct device* dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IMX_AUDMUX_V2_PDCR_RXDSEL (scalar_t__) ; 
 int IMX_AUDMUX_V2_PTCR_SYN ; 
 int IMX_AUDMUX_V2_PTCR_TCLKDIR ; 
 int IMX_AUDMUX_V2_PTCR_TCSEL (scalar_t__) ; 
 int IMX_AUDMUX_V2_PTCR_TFSDIR ; 
 int IMX_AUDMUX_V2_PTCR_TFSEL (scalar_t__) ; 
 scalar_t__ MUX_PORT_MAX ; 
 int SND_SOC_DAIFMT_CBM_CFM ; 
 int SND_SOC_DAIFMT_I2S ; 
 int SND_SOC_DAIFMT_NB_NF ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int imx_audmux_v2_configure_port (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_es8328_dai_init ; 
 int /*<<< orphan*/  imx_es8328_dapm_widgets ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct imx_es8328_data*) ; 
 int snd_soc_of_parse_audio_routing (TYPE_2__*,char*) ; 
 int snd_soc_of_parse_card_name (TYPE_2__*,char*) ; 
 int snd_soc_register_card (TYPE_2__*) ; 

__attribute__((used)) static int imx_es8328_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct device_node *ssi_np = NULL, *codec_np = NULL;
	struct platform_device *ssi_pdev;
	struct imx_es8328_data *data;
	struct snd_soc_dai_link_component *comp;
	u32 int_port, ext_port;
	int ret;
	struct device *dev = &pdev->dev;

	ret = of_property_read_u32(np, "mux-int-port", &int_port);
	if (ret) {
		dev_err(dev, "mux-int-port missing or invalid\n");
		goto fail;
	}
	if (int_port > MUX_PORT_MAX || int_port == 0) {
		dev_err(dev, "mux-int-port: hardware only has %d mux ports\n",
			MUX_PORT_MAX);
		goto fail;
	}

	ret = of_property_read_u32(np, "mux-ext-port", &ext_port);
	if (ret) {
		dev_err(dev, "mux-ext-port missing or invalid\n");
		goto fail;
	}
	if (ext_port > MUX_PORT_MAX || ext_port == 0) {
		dev_err(dev, "mux-ext-port: hardware only has %d mux ports\n",
			MUX_PORT_MAX);
		ret = -EINVAL;
		goto fail;
	}

	/*
	 * The port numbering in the hardware manual starts at 1, while
	 * the audmux API expects it starts at 0.
	 */
	int_port--;
	ext_port--;
	ret = imx_audmux_v2_configure_port(int_port,
			IMX_AUDMUX_V2_PTCR_SYN |
			IMX_AUDMUX_V2_PTCR_TFSEL(ext_port) |
			IMX_AUDMUX_V2_PTCR_TCSEL(ext_port) |
			IMX_AUDMUX_V2_PTCR_TFSDIR |
			IMX_AUDMUX_V2_PTCR_TCLKDIR,
			IMX_AUDMUX_V2_PDCR_RXDSEL(ext_port));
	if (ret) {
		dev_err(dev, "audmux internal port setup failed\n");
		return ret;
	}
	ret = imx_audmux_v2_configure_port(ext_port,
			IMX_AUDMUX_V2_PTCR_SYN,
			IMX_AUDMUX_V2_PDCR_RXDSEL(int_port));
	if (ret) {
		dev_err(dev, "audmux external port setup failed\n");
		return ret;
	}

	ssi_np = of_parse_phandle(pdev->dev.of_node, "ssi-controller", 0);
	codec_np = of_parse_phandle(pdev->dev.of_node, "audio-codec", 0);
	if (!ssi_np || !codec_np) {
		dev_err(dev, "phandle missing or invalid\n");
		ret = -EINVAL;
		goto fail;
	}

	ssi_pdev = of_find_device_by_node(ssi_np);
	if (!ssi_pdev) {
		dev_err(dev, "failed to find SSI platform device\n");
		ret = -EINVAL;
		goto fail;
	}

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data) {
		ret = -ENOMEM;
		goto fail;
	}

	comp = devm_kzalloc(dev, 3 * sizeof(*comp), GFP_KERNEL);
	if (!comp) {
		ret = -ENOMEM;
		goto fail;
	}

	data->dev = dev;

	data->jack_gpio = of_get_named_gpio(pdev->dev.of_node, "jack-gpio", 0);

	data->dai.cpus		= &comp[0];
	data->dai.codecs	= &comp[1];
	data->dai.platforms	= &comp[2];

	data->dai.num_cpus	= 1;
	data->dai.num_codecs	= 1;
	data->dai.num_platforms	= 1;

	data->dai.name = "hifi";
	data->dai.stream_name = "hifi";
	data->dai.codecs->dai_name = "es8328-hifi-analog";
	data->dai.codecs->of_node = codec_np;
	data->dai.cpus->of_node = ssi_np;
	data->dai.platforms->of_node = ssi_np;
	data->dai.init = &imx_es8328_dai_init;
	data->dai.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			    SND_SOC_DAIFMT_CBM_CFM;

	data->card.dev = dev;
	data->card.dapm_widgets = imx_es8328_dapm_widgets;
	data->card.num_dapm_widgets = ARRAY_SIZE(imx_es8328_dapm_widgets);
	ret = snd_soc_of_parse_card_name(&data->card, "model");
	if (ret) {
		dev_err(dev, "Unable to parse card name\n");
		goto fail;
	}
	ret = snd_soc_of_parse_audio_routing(&data->card, "audio-routing");
	if (ret) {
		dev_err(dev, "Unable to parse routing: %d\n", ret);
		goto fail;
	}
	data->card.num_links = 1;
	data->card.owner = THIS_MODULE;
	data->card.dai_link = &data->dai;

	ret = snd_soc_register_card(&data->card);
	if (ret) {
		dev_err(dev, "Unable to register: %d\n", ret);
		goto fail;
	}

	platform_set_drvdata(pdev, data);
fail:
	of_node_put(ssi_np);
	of_node_put(codec_np);

	return ret;
}