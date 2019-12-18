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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  addr_width; } ;
struct sun4i_i2s {int slots; int slot_width; int /*<<< orphan*/  field_fmt_sr; int /*<<< orphan*/  field_fmt_wss; TYPE_2__* variant; TYPE_1__ playback_dma_data; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_4__ {int (* set_chan_cfg ) (struct sun4i_i2s*,struct snd_pcm_hw_params*) ;int (* get_sr ) (struct sun4i_i2s*,unsigned int) ;int (* get_wss ) (struct sun4i_i2s*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 int params_physical_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 unsigned int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,int) ; 
 struct sun4i_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int stub1 (struct sun4i_i2s*,struct snd_pcm_hw_params*) ; 
 int stub2 (struct sun4i_i2s*,unsigned int) ; 
 int stub3 (struct sun4i_i2s*,unsigned int) ; 
 int sun4i_i2s_set_clk_rate (struct snd_soc_dai*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int sun4i_i2s_hw_params(struct snd_pcm_substream *substream,
			       struct snd_pcm_hw_params *params,
			       struct snd_soc_dai *dai)
{
	struct sun4i_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	unsigned int word_size = params_width(params);
	unsigned int slot_width = params_physical_width(params);
	unsigned int channels = params_channels(params);
	unsigned int slots = channels;
	int ret, sr, wss;
	u32 width;

	if (i2s->slots)
		slots = i2s->slots;

	if (i2s->slot_width)
		slot_width = i2s->slot_width;

	ret = i2s->variant->set_chan_cfg(i2s, params);
	if (ret < 0) {
		dev_err(dai->dev, "Invalid channel configuration\n");
		return ret;
	}

	switch (params_physical_width(params)) {
	case 16:
		width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		break;
	default:
		dev_err(dai->dev, "Unsupported physical sample width: %d\n",
			params_physical_width(params));
		return -EINVAL;
	}
	i2s->playback_dma_data.addr_width = width;

	sr = i2s->variant->get_sr(i2s, word_size);
	if (sr < 0)
		return -EINVAL;

	wss = i2s->variant->get_wss(i2s, slot_width);
	if (wss < 0)
		return -EINVAL;

	regmap_field_write(i2s->field_fmt_wss, wss);
	regmap_field_write(i2s->field_fmt_sr, sr);

	return sun4i_i2s_set_clk_rate(dai, params_rate(params),
				      slots, slot_width);
}