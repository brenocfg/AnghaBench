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
typedef  unsigned int u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct da7219_priv {int /*<<< orphan*/  tdm_en; scalar_t__ master; struct clk** dai_clks; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 size_t DA7219_DAI_BCLK_IDX ; 
 int DA7219_DAI_CH_NUM_MASK ; 
 unsigned int DA7219_DAI_CH_NUM_MAX ; 
 unsigned int DA7219_DAI_CH_NUM_SHIFT ; 
 int /*<<< orphan*/  DA7219_DAI_CTRL ; 
 size_t DA7219_DAI_WCLK_IDX ; 
 int DA7219_DAI_WORD_LENGTH_MASK ; 
 unsigned int DA7219_DAI_WORD_LENGTH_S16_LE ; 
 unsigned int DA7219_DAI_WORD_LENGTH_S20_LE ; 
 unsigned int DA7219_DAI_WORD_LENGTH_S24_LE ; 
 unsigned int DA7219_DAI_WORD_LENGTH_S32_LE ; 
 int EINVAL ; 
 unsigned long clk_round_rate (struct clk*,unsigned long) ; 
 int clk_set_rate (struct clk*,unsigned long) ; 
 int da7219_set_bclks_per_wclk (struct snd_soc_component*,int) ; 
 int da7219_set_sr (struct snd_soc_component*,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 unsigned long params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct da7219_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int da7219_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	struct clk *wclk = da7219->dai_clks[DA7219_DAI_WCLK_IDX];
	struct clk *bclk = da7219->dai_clks[DA7219_DAI_BCLK_IDX];
	u8 dai_ctrl = 0;
	unsigned int channels;
	unsigned long sr, bclk_rate;
	int word_len = params_width(params);
	int frame_size, ret;

	switch (word_len) {
	case 16:
		dai_ctrl |= DA7219_DAI_WORD_LENGTH_S16_LE;
		break;
	case 20:
		dai_ctrl |= DA7219_DAI_WORD_LENGTH_S20_LE;
		break;
	case 24:
		dai_ctrl |= DA7219_DAI_WORD_LENGTH_S24_LE;
		break;
	case 32:
		dai_ctrl |= DA7219_DAI_WORD_LENGTH_S32_LE;
		break;
	default:
		return -EINVAL;
	}

	channels = params_channels(params);
	if ((channels < 1) || (channels > DA7219_DAI_CH_NUM_MAX)) {
		dev_err(component->dev,
			"Invalid number of channels, only 1 to %d supported\n",
			DA7219_DAI_CH_NUM_MAX);
		return -EINVAL;
	}
	dai_ctrl |= channels << DA7219_DAI_CH_NUM_SHIFT;

	sr = params_rate(params);
	if (da7219->master && wclk) {
		ret = clk_set_rate(wclk, sr);
		if (ret) {
			dev_err(component->dev,
				"Failed to set WCLK SR %lu: %d\n", sr, ret);
			return ret;
		}
	} else {
		ret = da7219_set_sr(component, sr);
		if (ret) {
			dev_err(component->dev,
				"Failed to set SR %lu: %d\n", sr, ret);
			return ret;
		}
	}

	/*
	 * If we're master, then we have a limited set of BCLK rates we
	 * support. For slave mode this isn't the case and the codec can detect
	 * the BCLK rate automatically.
	 */
	if (da7219->master && !da7219->tdm_en) {
		if ((word_len * DA7219_DAI_CH_NUM_MAX) <= 32)
			frame_size = 32;
		else
			frame_size = 64;

		if (bclk) {
			bclk_rate = frame_size * sr;
			/*
			 * Rounding the rate here avoids failure trying to set a
			 * new rate on an already enabled bclk. In that
			 * instance this will just set the same rate as is
			 * currently in use, and so should continue without
			 * problem, as long as the BCLK rate is suitable for the
			 * desired frame size.
			 */
			bclk_rate = clk_round_rate(bclk, bclk_rate);
			if ((bclk_rate / sr) < frame_size) {
				dev_err(component->dev,
					"BCLK rate mismatch against frame size");
				return -EINVAL;
			}

			ret = clk_set_rate(bclk, bclk_rate);
			if (ret) {
				dev_err(component->dev,
					"Failed to set BCLK rate %lu: %d\n",
					bclk_rate, ret);
				return ret;
			}
		} else {
			ret = da7219_set_bclks_per_wclk(component, frame_size);
			if (ret) {
				dev_err(component->dev,
					"Failed to set BCLKs per WCLK %d: %d\n",
					frame_size, ret);
				return ret;
			}
		}
	}

	snd_soc_component_update_bits(component, DA7219_DAI_CTRL,
			    DA7219_DAI_WORD_LENGTH_MASK |
			    DA7219_DAI_CH_NUM_MASK,
			    dai_ctrl);

	return 0;
}