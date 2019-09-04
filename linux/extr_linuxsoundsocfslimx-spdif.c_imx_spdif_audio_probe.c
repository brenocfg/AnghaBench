#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_8__ {int num_links; int /*<<< orphan*/  owner; TYPE_1__* dai_link; TYPE_3__* dev; } ;
struct TYPE_7__ {char* name; char* stream_name; char* codec_dai_name; char* codec_name; int playback_only; int capture_only; struct device_node* platform_of_node; struct device_node* cpu_of_node; } ;
struct imx_spdif_data {TYPE_2__ card; TYPE_1__ dai; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 struct imx_spdif_data* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int snd_soc_of_parse_card_name (TYPE_2__*,char*) ; 

__attribute__((used)) static int imx_spdif_audio_probe(struct platform_device *pdev)
{
	struct device_node *spdif_np, *np = pdev->dev.of_node;
	struct imx_spdif_data *data;
	int ret = 0;

	spdif_np = of_parse_phandle(np, "spdif-controller", 0);
	if (!spdif_np) {
		dev_err(&pdev->dev, "failed to find spdif-controller\n");
		ret = -EINVAL;
		goto end;
	}

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data) {
		ret = -ENOMEM;
		goto end;
	}

	data->dai.name = "S/PDIF PCM";
	data->dai.stream_name = "S/PDIF PCM";
	data->dai.codec_dai_name = "snd-soc-dummy-dai";
	data->dai.codec_name = "snd-soc-dummy";
	data->dai.cpu_of_node = spdif_np;
	data->dai.platform_of_node = spdif_np;
	data->dai.playback_only = true;
	data->dai.capture_only = true;

	if (of_property_read_bool(np, "spdif-out"))
		data->dai.capture_only = false;

	if (of_property_read_bool(np, "spdif-in"))
		data->dai.playback_only = false;

	if (data->dai.playback_only && data->dai.capture_only) {
		dev_err(&pdev->dev, "no enabled S/PDIF DAI link\n");
		goto end;
	}

	data->card.dev = &pdev->dev;
	data->card.dai_link = &data->dai;
	data->card.num_links = 1;
	data->card.owner = THIS_MODULE;

	ret = snd_soc_of_parse_card_name(&data->card, "model");
	if (ret)
		goto end;

	ret = devm_snd_soc_register_card(&pdev->dev, &data->card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed: %d\n", ret);
		goto end;
	}

end:
	of_node_put(spdif_np);

	return ret;
}