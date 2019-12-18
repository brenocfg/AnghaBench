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
struct sun4i_i2s {int slots; int format; int /*<<< orphan*/  regmap; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_DSP_A 132 
#define  SND_SOC_DAIFMT_DSP_B 131 
 int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  SUN4I_I2S_CHAN_SEL (unsigned int) ; 
 int /*<<< orphan*/  SUN4I_I2S_CHAN_SEL_MASK ; 
 int /*<<< orphan*/  SUN4I_I2S_FMT0_REG ; 
 int /*<<< orphan*/  SUN8I_I2S_CHAN_CFG_REG ; 
 int /*<<< orphan*/  SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM (unsigned int) ; 
 int /*<<< orphan*/  SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM_MASK ; 
 int /*<<< orphan*/  SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM (unsigned int) ; 
 int /*<<< orphan*/  SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM_MASK ; 
 int /*<<< orphan*/  SUN8I_I2S_FMT0_LRCK_PERIOD (unsigned int) ; 
 int /*<<< orphan*/  SUN8I_I2S_FMT0_LRCK_PERIOD_MASK ; 
 int /*<<< orphan*/  SUN8I_I2S_RX_CHAN_MAP_REG ; 
 int /*<<< orphan*/  SUN8I_I2S_RX_CHAN_SEL_REG ; 
 int /*<<< orphan*/  SUN8I_I2S_TX_CHAN_EN (unsigned int) ; 
 int /*<<< orphan*/  SUN8I_I2S_TX_CHAN_EN_MASK ; 
 int /*<<< orphan*/  SUN8I_I2S_TX_CHAN_MAP_REG ; 
 int /*<<< orphan*/  SUN8I_I2S_TX_CHAN_SEL_REG ; 
 unsigned int params_channels (struct snd_pcm_hw_params const*) ; 
 unsigned int params_physical_width (struct snd_pcm_hw_params const*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sun8i_i2s_set_chan_cfg(const struct sun4i_i2s *i2s,
				  const struct snd_pcm_hw_params *params)
{
	unsigned int channels = params_channels(params);
	unsigned int slots = channels;
	unsigned int lrck_period;

	if (i2s->slots)
		slots = i2s->slots;

	/* Map the channels for playback and capture */
	regmap_write(i2s->regmap, SUN8I_I2S_TX_CHAN_MAP_REG, 0x76543210);
	regmap_write(i2s->regmap, SUN8I_I2S_RX_CHAN_MAP_REG, 0x76543210);

	/* Configure the channels */
	regmap_update_bits(i2s->regmap, SUN8I_I2S_TX_CHAN_SEL_REG,
			   SUN4I_I2S_CHAN_SEL_MASK,
			   SUN4I_I2S_CHAN_SEL(channels));
	regmap_update_bits(i2s->regmap, SUN8I_I2S_RX_CHAN_SEL_REG,
			   SUN4I_I2S_CHAN_SEL_MASK,
			   SUN4I_I2S_CHAN_SEL(channels));

	regmap_update_bits(i2s->regmap, SUN8I_I2S_CHAN_CFG_REG,
			   SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM_MASK,
			   SUN8I_I2S_CHAN_CFG_TX_SLOT_NUM(channels));
	regmap_update_bits(i2s->regmap, SUN8I_I2S_CHAN_CFG_REG,
			   SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM_MASK,
			   SUN8I_I2S_CHAN_CFG_RX_SLOT_NUM(channels));

	switch (i2s->format & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
	case SND_SOC_DAIFMT_LEFT_J:
	case SND_SOC_DAIFMT_RIGHT_J:
		lrck_period = params_physical_width(params) * slots;
		break;

	case SND_SOC_DAIFMT_I2S:
		lrck_period = params_physical_width(params);
		break;

	default:
		return -EINVAL;
	}

	regmap_update_bits(i2s->regmap, SUN4I_I2S_FMT0_REG,
			   SUN8I_I2S_FMT0_LRCK_PERIOD_MASK,
			   SUN8I_I2S_FMT0_LRCK_PERIOD(lrck_period));

	regmap_update_bits(i2s->regmap, SUN8I_I2S_TX_CHAN_SEL_REG,
			   SUN8I_I2S_TX_CHAN_EN_MASK,
			   SUN8I_I2S_TX_CHAN_EN(channels));

	return 0;
}