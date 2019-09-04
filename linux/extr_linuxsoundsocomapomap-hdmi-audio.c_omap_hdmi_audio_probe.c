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
struct snd_soc_dai_driver {int dummy; } ;
struct snd_soc_card {int num_links; struct device* dev; TYPE_2__* dai_link; scalar_t__ name; int /*<<< orphan*/  owner; } ;
struct device {struct omap_hdmi_audio_pdata* platform_data; } ;
struct platform_device {struct device dev; } ;
struct omap_hdmi_audio_pdata {int version; int /*<<< orphan*/  audio_dma_addr; int /*<<< orphan*/  ops; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {char* filter_data; int /*<<< orphan*/  addr_width; int /*<<< orphan*/  addr; } ;
struct hdmi_audio_data {struct snd_soc_card* card; int /*<<< orphan*/  dssdev; int /*<<< orphan*/  current_stream_lock; TYPE_1__ dma_data; int /*<<< orphan*/  ops; } ;
struct TYPE_4__ {char* codec_name; char* codec_dai_name; void* platform_name; void* cpu_dai_name; scalar_t__ stream_name; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct hdmi_audio_data*) ; 
 scalar_t__ devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,void*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct snd_soc_dai_driver omap4_hdmi_dai ; 
 struct snd_soc_dai_driver omap5_hdmi_dai ; 
 int /*<<< orphan*/  omap_hdmi_component ; 
 int sdma_pcm_platform_register (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct hdmi_audio_data*) ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 
 int snd_soc_register_component (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct snd_soc_dai_driver*,int) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_hdmi_audio_probe(struct platform_device *pdev)
{
	struct omap_hdmi_audio_pdata *ha = pdev->dev.platform_data;
	struct device *dev = &pdev->dev;
	struct hdmi_audio_data *ad;
	struct snd_soc_dai_driver *dai_drv;
	struct snd_soc_card *card;
	int ret;

	if (!ha) {
		dev_err(dev, "No platform data\n");
		return -EINVAL;
	}

	ad = devm_kzalloc(dev, sizeof(*ad), GFP_KERNEL);
	if (!ad)
		return -ENOMEM;
	ad->dssdev = ha->dev;
	ad->ops = ha->ops;
	ad->dma_data.addr = ha->audio_dma_addr;
	ad->dma_data.filter_data = "audio_tx";
	ad->dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	mutex_init(&ad->current_stream_lock);

	switch (ha->version) {
	case 4:
		dai_drv = &omap4_hdmi_dai;
		break;
	case 5:
		dai_drv = &omap5_hdmi_dai;
		break;
	default:
		return -EINVAL;
	}
	ret = snd_soc_register_component(ad->dssdev, &omap_hdmi_component,
					 dai_drv, 1);
	if (ret)
		return ret;

	ret = sdma_pcm_platform_register(ad->dssdev, "audio_tx", NULL);
	if (ret)
		return ret;

	card = devm_kzalloc(dev, sizeof(*card), GFP_KERNEL);
	if (!card)
		return -ENOMEM;

	card->name = devm_kasprintf(dev, GFP_KERNEL,
				    "HDMI %s", dev_name(ad->dssdev));
	if (!card->name)
		return -ENOMEM;

	card->owner = THIS_MODULE;
	card->dai_link =
		devm_kzalloc(dev, sizeof(*(card->dai_link)), GFP_KERNEL);
	if (!card->dai_link)
		return -ENOMEM;
	card->dai_link->name = card->name;
	card->dai_link->stream_name = card->name;
	card->dai_link->cpu_dai_name = dev_name(ad->dssdev);
	card->dai_link->platform_name = dev_name(ad->dssdev);
	card->dai_link->codec_name = "snd-soc-dummy";
	card->dai_link->codec_dai_name = "snd-soc-dummy-dai";
	card->num_links = 1;
	card->dev = dev;

	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(dev, "snd_soc_register_card failed (%d)\n", ret);
		snd_soc_unregister_component(ad->dssdev);
		return ret;
	}

	ad->card = card;
	snd_soc_card_set_drvdata(card, ad);

	dev_set_drvdata(dev, ad);

	return 0;
}