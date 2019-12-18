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
struct regmap {int dummy; } ;
struct axg_tdm_stream {TYPE_1__* iface; } ;
struct axg_tdm_formatter_hw {unsigned int skew_offset; } ;
struct TYPE_2__ {int fmt; scalar_t__ slot_width; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_DSP_A 132 
#define  SND_SOC_DAIFMT_DSP_B 131 
 int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  TDMIN_CTRL ; 
 unsigned int TDMIN_CTRL_BITNUM (scalar_t__) ; 
 unsigned int TDMIN_CTRL_BITNUM_MASK ; 
 unsigned int TDMIN_CTRL_I2S_MODE ; 
 unsigned int TDMIN_CTRL_IN_BIT_SKEW (unsigned int) ; 
 unsigned int TDMIN_CTRL_IN_BIT_SKEW_MASK ; 
 unsigned int TDMIN_CTRL_LSB_FIRST ; 
 unsigned int TDMIN_CTRL_WS_INV ; 
 int /*<<< orphan*/  TDMIN_MASK0 ; 
 int /*<<< orphan*/  TDMIN_SWAP ; 
 int axg_tdm_formatter_set_channel_masks (struct regmap*,struct axg_tdm_stream*,int /*<<< orphan*/ ) ; 
 scalar_t__ axg_tdm_lrclk_invert (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int axg_tdmin_prepare(struct regmap *map,
			     const struct axg_tdm_formatter_hw *quirks,
			     struct axg_tdm_stream *ts)
{
	unsigned int val, skew = quirks->skew_offset;

	/* Set stream skew */
	switch (ts->iface->fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_DSP_A:
		skew += 1;
		break;

	case SND_SOC_DAIFMT_LEFT_J:
	case SND_SOC_DAIFMT_DSP_B:
		break;

	default:
		pr_err("Unsupported format: %u\n",
		       ts->iface->fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		return -EINVAL;
	}

	val = TDMIN_CTRL_IN_BIT_SKEW(skew);

	/* Set stream format mode */
	switch (ts->iface->fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_LEFT_J:
	case SND_SOC_DAIFMT_RIGHT_J:
		val |= TDMIN_CTRL_I2S_MODE;
		break;
	}

	/* If the sample clock is inverted, invert it back for the formatter */
	if (axg_tdm_lrclk_invert(ts->iface->fmt))
		val |= TDMIN_CTRL_WS_INV;

	/* Set the slot width */
	val |= TDMIN_CTRL_BITNUM(ts->iface->slot_width - 1);

	/*
	 * The following also reset LSB_FIRST which result in the formatter
	 * placing the first bit received at bit 31
	 */
	regmap_update_bits(map, TDMIN_CTRL,
			   (TDMIN_CTRL_IN_BIT_SKEW_MASK | TDMIN_CTRL_WS_INV |
			    TDMIN_CTRL_I2S_MODE | TDMIN_CTRL_LSB_FIRST |
			    TDMIN_CTRL_BITNUM_MASK), val);

	/* Set static swap mask configuration */
	regmap_write(map, TDMIN_SWAP, 0x76543210);

	return axg_tdm_formatter_set_channel_masks(map, ts, TDMIN_MASK0);
}