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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct axg_spdifout {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPDIFOUT_CTRL0 ; 
 int SPDIFOUT_CTRL0_DATA_SEL ; 
 unsigned int SPDIFOUT_CTRL0_MASK (int) ; 
 int SPDIFOUT_CTRL0_MASK_MASK ; 
 int SPDIFOUT_CTRL0_MSB_FIRST ; 
 int /*<<< orphan*/  SPDIFOUT_CTRL1 ; 
 unsigned int SPDIFOUT_CTRL1_MSB_POS (scalar_t__) ; 
 int SPDIFOUT_CTRL1_MSB_POS_MASK ; 
 unsigned int SPDIFOUT_CTRL1_TYPE (int) ; 
 int SPDIFOUT_CTRL1_TYPE_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_physical_width (struct snd_pcm_hw_params*) ; 
 scalar_t__ params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct axg_spdifout* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int axg_spdifout_sample_fmt(struct snd_pcm_hw_params *params,
				   struct snd_soc_dai *dai)
{
	struct axg_spdifout *priv = snd_soc_dai_get_drvdata(dai);
	unsigned int val;

	/* Set the samples spdifout will pull from the FIFO */
	switch (params_channels(params)) {
	case 1:
		val = SPDIFOUT_CTRL0_MASK(0x1);
		break;
	case 2:
		val = SPDIFOUT_CTRL0_MASK(0x3);
		break;
	default:
		dev_err(dai->dev, "too many channels for spdif dai: %u\n",
			params_channels(params));
		return -EINVAL;
	}

	regmap_update_bits(priv->map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_MASK_MASK, val);

	/* FIFO data are arranged in chunks of 64bits */
	switch (params_physical_width(params)) {
	case 8:
		/* 8 samples of 8 bits */
		val = SPDIFOUT_CTRL1_TYPE(0);
		break;
	case 16:
		/* 4 samples of 16 bits - right justified */
		val = SPDIFOUT_CTRL1_TYPE(2);
		break;
	case 32:
		/* 2 samples of 32 bits - right justified */
		val = SPDIFOUT_CTRL1_TYPE(4);
		break;
	default:
		dev_err(dai->dev, "Unsupported physical width: %u\n",
			params_physical_width(params));
		return -EINVAL;
	}

	/* Position of the MSB in FIFO samples */
	val |= SPDIFOUT_CTRL1_MSB_POS(params_width(params) - 1);

	regmap_update_bits(priv->map, SPDIFOUT_CTRL1,
			   SPDIFOUT_CTRL1_MSB_POS_MASK |
			   SPDIFOUT_CTRL1_TYPE_MASK, val);

	regmap_update_bits(priv->map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_MSB_FIRST | SPDIFOUT_CTRL0_DATA_SEL,
			   0);

	return 0;
}