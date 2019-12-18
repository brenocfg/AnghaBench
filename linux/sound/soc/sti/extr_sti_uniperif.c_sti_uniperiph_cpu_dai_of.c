#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct uniperif {scalar_t__ irq; int type; TYPE_1__* hw; int /*<<< orphan*/  dai_ops; TYPE_4__* mem_region; scalar_t__ fifo_phys_address; int /*<<< orphan*/  base; int /*<<< orphan*/  ver; int /*<<< orphan*/  id; } ;
struct sti_uniperiph_dev_data {int type; scalar_t__ stream; int /*<<< orphan*/  dai_names; int /*<<< orphan*/  version; int /*<<< orphan*/  id; } ;
struct sti_uniperiph_dai {scalar_t__ stream; struct uniperif* uni; } ;
struct sti_uniperiph_data {TYPE_2__* pdev; struct sti_uniperiph_dai dai_data; struct snd_soc_dai_driver* dai; } ;
struct snd_soc_pcm_stream {int /*<<< orphan*/  formats; int /*<<< orphan*/  rates; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; int /*<<< orphan*/  stream_name; } ;
struct snd_soc_dai_driver {int /*<<< orphan*/  name; int /*<<< orphan*/  ops; struct snd_soc_pcm_stream capture; struct snd_soc_pcm_stream playback; } ;
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_10__ {scalar_t__ start; } ;
struct TYPE_9__ {struct device dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  formats; int /*<<< orphan*/  rates; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int SND_ST_UNIPERIF_TYPE_PCM ; 
 int SND_ST_UNIPERIF_TYPE_TDM ; 
 scalar_t__ UNIPERIF_FIFO_DATA_OFFSET (struct uniperif*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,TYPE_4__*) ; 
 struct uniperif* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,char const**) ; 
 scalar_t__ platform_get_irq (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* platform_get_resource (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_sti_match ; 
 struct snd_soc_dai_driver sti_uniperiph_dai_template ; 
 int uni_player_init (TYPE_2__*,struct uniperif*) ; 
 int uni_reader_init (TYPE_2__*,struct uniperif*) ; 

__attribute__((used)) static int sti_uniperiph_cpu_dai_of(struct device_node *node,
				    struct sti_uniperiph_data *priv)
{
	struct device *dev = &priv->pdev->dev;
	struct sti_uniperiph_dai *dai_data = &priv->dai_data;
	struct snd_soc_dai_driver *dai = priv->dai;
	struct snd_soc_pcm_stream *stream;
	struct uniperif *uni;
	const struct of_device_id *of_id;
	const struct sti_uniperiph_dev_data *dev_data;
	const char *mode;
	int ret;

	/* Populate data structure depending on compatibility */
	of_id = of_match_node(snd_soc_sti_match, node);
	if (!of_id->data) {
		dev_err(dev, "data associated to device is missing\n");
		return -EINVAL;
	}
	dev_data = (struct sti_uniperiph_dev_data *)of_id->data;

	uni = devm_kzalloc(dev, sizeof(*uni), GFP_KERNEL);
	if (!uni)
		return -ENOMEM;

	uni->id = dev_data->id;
	uni->ver = dev_data->version;

	*dai = sti_uniperiph_dai_template;
	dai->name = dev_data->dai_names;

	/* Get resources */
	uni->mem_region = platform_get_resource(priv->pdev, IORESOURCE_MEM, 0);

	if (!uni->mem_region) {
		dev_err(dev, "Failed to get memory resource\n");
		return -ENODEV;
	}

	uni->base = devm_ioremap_resource(dev, uni->mem_region);

	if (IS_ERR(uni->base))
		return PTR_ERR(uni->base);

	uni->fifo_phys_address = uni->mem_region->start +
				     UNIPERIF_FIFO_DATA_OFFSET(uni);

	uni->irq = platform_get_irq(priv->pdev, 0);
	if (uni->irq < 0)
		return -ENXIO;

	uni->type = dev_data->type;

	/* check if player should be configured for tdm */
	if (dev_data->type & SND_ST_UNIPERIF_TYPE_TDM) {
		if (!of_property_read_string(node, "st,tdm-mode", &mode))
			uni->type = SND_ST_UNIPERIF_TYPE_TDM;
		else
			uni->type = SND_ST_UNIPERIF_TYPE_PCM;
	}

	dai_data->uni = uni;
	dai_data->stream = dev_data->stream;

	if (priv->dai_data.stream == SNDRV_PCM_STREAM_PLAYBACK) {
		ret = uni_player_init(priv->pdev, uni);
		stream = &dai->playback;
	} else {
		ret = uni_reader_init(priv->pdev, uni);
		stream = &dai->capture;
	}
	if (ret < 0)
		return ret;

	dai->ops = uni->dai_ops;

	stream->stream_name = dai->name;
	stream->channels_min = uni->hw->channels_min;
	stream->channels_max = uni->hw->channels_max;
	stream->rates = uni->hw->rates;
	stream->formats = uni->hw->formats;

	return 0;
}