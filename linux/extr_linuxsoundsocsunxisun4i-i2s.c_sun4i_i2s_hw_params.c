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
struct sun4i_i2s {TYPE_2__* variant; int /*<<< orphan*/  field_fmt_sr; int /*<<< orphan*/  field_fmt_wss; TYPE_1__ playback_dma_data; int /*<<< orphan*/  regmap; int /*<<< orphan*/  field_rxchansel; int /*<<< orphan*/  field_txchansel; int /*<<< orphan*/  field_rxchanmap; int /*<<< orphan*/  field_txchanmap; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_4__ {int fmt_offset; scalar_t__ has_chsel_tx_chen; scalar_t__ has_chcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int EINVAL ; 
 int SUN4I_I2S_CHAN_SEL (int) ; 
 int /*<<< orphan*/  SUN8I_I2S_CHAN_CFG_REG ; 
 int /*<<< orphan*/  SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM (int) ; 
 int /*<<< orphan*/  SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM_MASK ; 
 int /*<<< orphan*/  SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM (int) ; 
 int /*<<< orphan*/  SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM_MASK ; 
 int /*<<< orphan*/  SUN8I_I2S_TX_CHAN_EN (int) ; 
 int /*<<< orphan*/  SUN8I_I2S_TX_CHAN_EN_MASK ; 
 int /*<<< orphan*/  SUN8I_I2S_TX_CHAN_SEL_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_physical_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sun4i_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int sun4i_i2s_set_clk_rate (struct snd_soc_dai*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sun4i_i2s_hw_params(struct snd_pcm_substream *substream,
			       struct snd_pcm_hw_params *params,
			       struct snd_soc_dai *dai)
{
	struct sun4i_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	int sr, wss, channels;
	u32 width;

	channels = params_channels(params);
	if (channels != 2) {
		dev_err(dai->dev, "Unsupported number of channels: %d\n",
			channels);
		return -EINVAL;
	}

	if (i2s->variant->has_chcfg) {
		regmap_update_bits(i2s->regmap, SUN8I_I2S_CHAN_CFG_REG,
				   SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM_MASK,
				   SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM(channels));
		regmap_update_bits(i2s->regmap, SUN8I_I2S_CHAN_CFG_REG,
				   SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM_MASK,
				   SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM(channels));
	}

	/* Map the channels for playback and capture */
	regmap_field_write(i2s->field_txchanmap, 0x76543210);
	regmap_field_write(i2s->field_rxchanmap, 0x00003210);

	/* Configure the channels */
	regmap_field_write(i2s->field_txchansel,
			   SUN4I_I2S_CHAN_SEL(params_channels(params)));

	regmap_field_write(i2s->field_rxchansel,
			   SUN4I_I2S_CHAN_SEL(params_channels(params)));

	if (i2s->variant->has_chsel_tx_chen)
		regmap_update_bits(i2s->regmap, SUN8I_I2S_TX_CHAN_SEL_REG,
				   SUN8I_I2S_TX_CHAN_EN_MASK,
				   SUN8I_I2S_TX_CHAN_EN(channels));

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

	switch (params_width(params)) {
	case 16:
		sr = 0;
		wss = 0;
		break;

	default:
		dev_err(dai->dev, "Unsupported sample width: %d\n",
			params_width(params));
		return -EINVAL;
	}

	regmap_field_write(i2s->field_fmt_wss,
			   wss + i2s->variant->fmt_offset);
	regmap_field_write(i2s->field_fmt_sr,
			   sr + i2s->variant->fmt_offset);

	return sun4i_i2s_set_clk_rate(dai, params_rate(params),
				      params_width(params));
}