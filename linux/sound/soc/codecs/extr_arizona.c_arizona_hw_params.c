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
struct snd_soc_dai {int id; TYPE_1__* driver; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct arizona_priv {struct arizona* arizona; } ;
struct TYPE_4__ {int* max_channels_clocked; } ;
struct arizona {int* tdm_width; int* tdm_slots; int /*<<< orphan*/  regmap; TYPE_2__ pdata; } ;
struct TYPE_3__ {int base; } ;

/* Variables and functions */
 int ARIZONA_AIF1RX_BCPF_MASK ; 
 int ARIZONA_AIF1RX_SLOT_LEN_MASK ; 
 int ARIZONA_AIF1RX_WL_MASK ; 
 int ARIZONA_AIF1TX_BCPF_MASK ; 
 int ARIZONA_AIF1TX_SLOT_LEN_MASK ; 
 int ARIZONA_AIF1TX_WL_MASK ; 
 int ARIZONA_AIF1TX_WL_SHIFT ; 
 int ARIZONA_AIF1_BCLK_FREQ_MASK ; 
 int ARIZONA_AIF1_FMT_MASK ; 
 scalar_t__ ARIZONA_AIF_BCLK_CTRL ; 
 scalar_t__ ARIZONA_AIF_FORMAT ; 
 scalar_t__ ARIZONA_AIF_FRAME_CTRL_1 ; 
 scalar_t__ ARIZONA_AIF_FRAME_CTRL_2 ; 
 scalar_t__ ARIZONA_AIF_RX_BCLK_RATE ; 
 scalar_t__ ARIZONA_AIF_RX_ENABLES ; 
 scalar_t__ ARIZONA_AIF_TX_BCLK_RATE ; 
 scalar_t__ ARIZONA_AIF_TX_ENABLES ; 
 int ARIZONA_FMT_I2S_MODE ; 
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int* arizona_44k1_bclk_rates ; 
 int* arizona_48k_bclk_rates ; 
 int arizona_aif_cfg_changed (struct snd_soc_component*,int,int,int,int) ; 
 int /*<<< orphan*/  arizona_aif_dbg (struct snd_soc_dai*,char*,...) ; 
 int /*<<< orphan*/  arizona_aif_err (struct snd_soc_dai*,char*,int const) ; 
 int arizona_hw_params_rate (struct snd_pcm_substream*,struct snd_pcm_hw_params*,struct snd_soc_dai*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int const params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits_async (int /*<<< orphan*/ ,scalar_t__,int,unsigned int) ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 void* snd_soc_component_read32 (struct snd_soc_component*,scalar_t__) ; 
 int snd_soc_params_to_bclk (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int arizona_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	struct arizona *arizona = priv->arizona;
	int base = dai->driver->base;
	const int *rates;
	int i, ret, val;
	int channels = params_channels(params);
	int chan_limit = arizona->pdata.max_channels_clocked[dai->id - 1];
	int tdm_width = arizona->tdm_width[dai->id - 1];
	int tdm_slots = arizona->tdm_slots[dai->id - 1];
	int bclk, lrclk, wl, frame, bclk_target;
	bool reconfig;
	unsigned int aif_tx_state, aif_rx_state;

	if (params_rate(params) % 4000)
		rates = &arizona_44k1_bclk_rates[0];
	else
		rates = &arizona_48k_bclk_rates[0];

	wl = params_width(params);

	if (tdm_slots) {
		arizona_aif_dbg(dai, "Configuring for %d %d bit TDM slots\n",
				tdm_slots, tdm_width);
		bclk_target = tdm_slots * tdm_width * params_rate(params);
		channels = tdm_slots;
	} else {
		bclk_target = snd_soc_params_to_bclk(params);
		tdm_width = wl;
	}

	if (chan_limit && chan_limit < channels) {
		arizona_aif_dbg(dai, "Limiting to %d channels\n", chan_limit);
		bclk_target /= channels;
		bclk_target *= chan_limit;
	}

	/* Force multiple of 2 channels for I2S mode */
	val = snd_soc_component_read32(component, base + ARIZONA_AIF_FORMAT);
	val &= ARIZONA_AIF1_FMT_MASK;
	if ((channels & 1) && (val == ARIZONA_FMT_I2S_MODE)) {
		arizona_aif_dbg(dai, "Forcing stereo mode\n");
		bclk_target /= channels;
		bclk_target *= channels + 1;
	}

	for (i = 0; i < ARRAY_SIZE(arizona_44k1_bclk_rates); i++) {
		if (rates[i] >= bclk_target &&
		    rates[i] % params_rate(params) == 0) {
			bclk = i;
			break;
		}
	}
	if (i == ARRAY_SIZE(arizona_44k1_bclk_rates)) {
		arizona_aif_err(dai, "Unsupported sample rate %dHz\n",
				params_rate(params));
		return -EINVAL;
	}

	lrclk = rates[bclk] / params_rate(params);

	arizona_aif_dbg(dai, "BCLK %dHz LRCLK %dHz\n",
			rates[bclk], rates[bclk] / lrclk);

	frame = wl << ARIZONA_AIF1TX_WL_SHIFT | tdm_width;

	reconfig = arizona_aif_cfg_changed(component, base, bclk, lrclk, frame);

	if (reconfig) {
		/* Save AIF TX/RX state */
		aif_tx_state = snd_soc_component_read32(component,
					    base + ARIZONA_AIF_TX_ENABLES);
		aif_rx_state = snd_soc_component_read32(component,
					    base + ARIZONA_AIF_RX_ENABLES);
		/* Disable AIF TX/RX before reconfiguring it */
		regmap_update_bits_async(arizona->regmap,
					 base + ARIZONA_AIF_TX_ENABLES,
					 0xff, 0x0);
		regmap_update_bits(arizona->regmap,
				   base + ARIZONA_AIF_RX_ENABLES, 0xff, 0x0);
	}

	ret = arizona_hw_params_rate(substream, params, dai);
	if (ret != 0)
		goto restore_aif;

	if (reconfig) {
		regmap_update_bits_async(arizona->regmap,
					 base + ARIZONA_AIF_BCLK_CTRL,
					 ARIZONA_AIF1_BCLK_FREQ_MASK, bclk);
		regmap_update_bits_async(arizona->regmap,
					 base + ARIZONA_AIF_TX_BCLK_RATE,
					 ARIZONA_AIF1TX_BCPF_MASK, lrclk);
		regmap_update_bits_async(arizona->regmap,
					 base + ARIZONA_AIF_RX_BCLK_RATE,
					 ARIZONA_AIF1RX_BCPF_MASK, lrclk);
		regmap_update_bits_async(arizona->regmap,
					 base + ARIZONA_AIF_FRAME_CTRL_1,
					 ARIZONA_AIF1TX_WL_MASK |
					 ARIZONA_AIF1TX_SLOT_LEN_MASK, frame);
		regmap_update_bits(arizona->regmap,
				   base + ARIZONA_AIF_FRAME_CTRL_2,
				   ARIZONA_AIF1RX_WL_MASK |
				   ARIZONA_AIF1RX_SLOT_LEN_MASK, frame);
	}

restore_aif:
	if (reconfig) {
		/* Restore AIF TX/RX state */
		regmap_update_bits_async(arizona->regmap,
					 base + ARIZONA_AIF_TX_ENABLES,
					 0xff, aif_tx_state);
		regmap_update_bits(arizona->regmap,
				   base + ARIZONA_AIF_RX_ENABLES,
				   0xff, aif_rx_state);
	}
	return ret;
}