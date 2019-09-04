#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sun4i_i2s {int /*<<< orphan*/  regmap; TYPE_1__* variant; int /*<<< orphan*/  field_fmt_lrclk; int /*<<< orphan*/  field_fmt_bclk; int /*<<< orphan*/  field_fmt_mode; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ has_slave_select_bit; scalar_t__ has_chsel_offset; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 136 
#define  SND_SOC_DAIFMT_CBS_CFS 135 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 131 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 130 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 scalar_t__ SUN4I_I2S_CTRL_MODE_MASK ; 
 scalar_t__ SUN4I_I2S_CTRL_MODE_MASTER ; 
 scalar_t__ SUN4I_I2S_CTRL_MODE_SLAVE ; 
 int /*<<< orphan*/  SUN4I_I2S_CTRL_REG ; 
 int /*<<< orphan*/  SUN4I_I2S_FIFO_CTRL_REG ; 
 scalar_t__ SUN4I_I2S_FIFO_CTRL_RX_MODE (int) ; 
 scalar_t__ SUN4I_I2S_FIFO_CTRL_RX_MODE_MASK ; 
 scalar_t__ SUN4I_I2S_FIFO_CTRL_TX_MODE (int) ; 
 scalar_t__ SUN4I_I2S_FIFO_CTRL_TX_MODE_MASK ; 
 scalar_t__ SUN4I_I2S_FMT0_FMT_I2S ; 
 scalar_t__ SUN4I_I2S_FMT0_FMT_LEFT_J ; 
 scalar_t__ SUN4I_I2S_FMT0_FMT_RIGHT_J ; 
 scalar_t__ SUN4I_I2S_FMT0_POLARITY_INVERTED ; 
 scalar_t__ SUN4I_I2S_FMT0_POLARITY_NORMAL ; 
 scalar_t__ SUN8I_I2S_CTRL_BCLK_OUT ; 
 scalar_t__ SUN8I_I2S_CTRL_LRCK_OUT ; 
 scalar_t__ SUN8I_I2S_TX_CHAN_OFFSET (scalar_t__) ; 
 scalar_t__ SUN8I_I2S_TX_CHAN_OFFSET_MASK ; 
 int /*<<< orphan*/  SUN8I_I2S_TX_CHAN_SEL_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct sun4i_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int sun4i_i2s_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct sun4i_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	u32 val;
	u32 offset = 0;
	u32 bclk_polarity = SUN4I_I2S_FMT0_POLARITY_NORMAL;
	u32 lrclk_polarity = SUN4I_I2S_FMT0_POLARITY_NORMAL;

	/* DAI Mode */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		val = SUN4I_I2S_FMT0_FMT_I2S;
		offset = 1;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		val = SUN4I_I2S_FMT0_FMT_LEFT_J;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		val = SUN4I_I2S_FMT0_FMT_RIGHT_J;
		break;
	default:
		dev_err(dai->dev, "Unsupported format: %d\n",
			fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		return -EINVAL;
	}

	if (i2s->variant->has_chsel_offset) {
		/*
		 * offset being set indicates that we're connected to an i2s
		 * device, however offset is only used on the sun8i block and
		 * i2s shares the same setting with the LJ format. Increment
		 * val so that the bit to value to write is correct.
		 */
		if (offset > 0)
			val++;
		/* blck offset determines whether i2s or LJ */
		regmap_update_bits(i2s->regmap, SUN8I_I2S_TX_CHAN_SEL_REG,
				   SUN8I_I2S_TX_CHAN_OFFSET_MASK,
				   SUN8I_I2S_TX_CHAN_OFFSET(offset));
	}

	regmap_field_write(i2s->field_fmt_mode, val);

	/* DAI clock polarity */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_IF:
		/* Invert both clocks */
		bclk_polarity = SUN4I_I2S_FMT0_POLARITY_INVERTED;
		lrclk_polarity = SUN4I_I2S_FMT0_POLARITY_INVERTED;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		/* Invert bit clock */
		bclk_polarity = SUN4I_I2S_FMT0_POLARITY_INVERTED;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		/* Invert frame clock */
		lrclk_polarity = SUN4I_I2S_FMT0_POLARITY_INVERTED;
		break;
	case SND_SOC_DAIFMT_NB_NF:
		break;
	default:
		dev_err(dai->dev, "Unsupported clock polarity: %d\n",
			fmt & SND_SOC_DAIFMT_INV_MASK);
		return -EINVAL;
	}

	regmap_field_write(i2s->field_fmt_bclk, bclk_polarity);
	regmap_field_write(i2s->field_fmt_lrclk, lrclk_polarity);

	if (i2s->variant->has_slave_select_bit) {
		/* DAI clock master masks */
		switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
		case SND_SOC_DAIFMT_CBS_CFS:
			/* BCLK and LRCLK master */
			val = SUN4I_I2S_CTRL_MODE_MASTER;
			break;
		case SND_SOC_DAIFMT_CBM_CFM:
			/* BCLK and LRCLK slave */
			val = SUN4I_I2S_CTRL_MODE_SLAVE;
			break;
		default:
			dev_err(dai->dev, "Unsupported slave setting: %d\n",
				fmt & SND_SOC_DAIFMT_MASTER_MASK);
			return -EINVAL;
		}
		regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
				   SUN4I_I2S_CTRL_MODE_MASK,
				   val);
	} else {
		/*
		 * The newer i2s block does not have a slave select bit,
		 * instead the clk pins are configured as inputs.
		 */
		/* DAI clock master masks */
		switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
		case SND_SOC_DAIFMT_CBS_CFS:
			/* BCLK and LRCLK master */
			val = SUN8I_I2S_CTRL_BCLK_OUT |
				SUN8I_I2S_CTRL_LRCK_OUT;
			break;
		case SND_SOC_DAIFMT_CBM_CFM:
			/* BCLK and LRCLK slave */
			val = 0;
			break;
		default:
			dev_err(dai->dev, "Unsupported slave setting: %d\n",
				fmt & SND_SOC_DAIFMT_MASTER_MASK);
			return -EINVAL;
		}
		regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
				   SUN8I_I2S_CTRL_BCLK_OUT |
				   SUN8I_I2S_CTRL_LRCK_OUT,
				   val);
	}

	/* Set significant bits in our FIFOs */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_FIFO_CTRL_REG,
			   SUN4I_I2S_FIFO_CTRL_TX_MODE_MASK |
			   SUN4I_I2S_FIFO_CTRL_RX_MODE_MASK,
			   SUN4I_I2S_FIFO_CTRL_TX_MODE(1) |
			   SUN4I_I2S_FIFO_CTRL_RX_MODE(1));
	return 0;
}