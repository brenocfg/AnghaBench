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
typedef  int u8 ;
typedef  unsigned long long u64 ;
typedef  unsigned int u32 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct da7213_priv {int mclk_rate; int /*<<< orphan*/  master; } ;
typedef  int frac_div ;

/* Variables and functions */
 unsigned long long DA7213_BYTE_MASK ; 
 unsigned long long DA7213_BYTE_SHIFT ; 
 int DA7213_PLL_32K_MODE ; 
 int /*<<< orphan*/  DA7213_PLL_CTRL ; 
 int DA7213_PLL_EN ; 
 int DA7213_PLL_FRAC_BOT ; 
 int DA7213_PLL_FRAC_TOP ; 
 unsigned int DA7213_PLL_FREQ_OUT_94310400 ; 
 int DA7213_PLL_INDIV_18_TO_36_MHZ ; 
 int DA7213_PLL_INDIV_18_TO_36_MHZ_VAL ; 
 int DA7213_PLL_INDIV_36_TO_54_MHZ ; 
 int DA7213_PLL_INDIV_36_TO_54_MHZ_VAL ; 
 int DA7213_PLL_INDIV_5_TO_9_MHZ ; 
 int DA7213_PLL_INDIV_5_TO_9_MHZ_VAL ; 
 int DA7213_PLL_INDIV_9_TO_18_MHZ ; 
 int DA7213_PLL_INDIV_9_TO_18_MHZ_VAL ; 
 int DA7213_PLL_INDIV_MASK ; 
 int DA7213_PLL_INTEGER ; 
 int DA7213_PLL_MODE_MASK ; 
 int DA7213_PLL_SRM_EN ; 
#define  DA7213_SYSCLK_MCLK 131 
#define  DA7213_SYSCLK_PLL 130 
#define  DA7213_SYSCLK_PLL_32KHZ 129 
#define  DA7213_SYSCLK_PLL_SRM 128 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned int) ; 
 struct da7213_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int,int) ; 

__attribute__((used)) static int da7213_set_dai_pll(struct snd_soc_dai *codec_dai, int pll_id,
			      int source, unsigned int fref, unsigned int fout)
{
	struct snd_soc_component *component = codec_dai->component;
	struct da7213_priv *da7213 = snd_soc_component_get_drvdata(component);

	u8 pll_ctrl, indiv_bits, indiv;
	u8 pll_frac_top, pll_frac_bot, pll_integer;
	u32 freq_ref;
	u64 frac_div;

	/* Workout input divider based on MCLK rate */
	if (da7213->mclk_rate == 32768) {
		if (!da7213->master) {
			dev_err(component->dev,
				"32KHz only valid if codec is clock master\n");
			return -EINVAL;
		}

		/* 32KHz PLL Mode */
		indiv_bits = DA7213_PLL_INDIV_9_TO_18_MHZ;
		indiv = DA7213_PLL_INDIV_9_TO_18_MHZ_VAL;
		source = DA7213_SYSCLK_PLL_32KHZ;
		freq_ref = 3750000;

	} else {
		if (da7213->mclk_rate < 5000000) {
			dev_err(component->dev,
				"PLL input clock %d below valid range\n",
				da7213->mclk_rate);
			return -EINVAL;
		} else if (da7213->mclk_rate <= 9000000) {
			indiv_bits = DA7213_PLL_INDIV_5_TO_9_MHZ;
			indiv = DA7213_PLL_INDIV_5_TO_9_MHZ_VAL;
		} else if (da7213->mclk_rate <= 18000000) {
			indiv_bits = DA7213_PLL_INDIV_9_TO_18_MHZ;
			indiv = DA7213_PLL_INDIV_9_TO_18_MHZ_VAL;
		} else if (da7213->mclk_rate <= 36000000) {
			indiv_bits = DA7213_PLL_INDIV_18_TO_36_MHZ;
			indiv = DA7213_PLL_INDIV_18_TO_36_MHZ_VAL;
		} else if (da7213->mclk_rate <= 54000000) {
			indiv_bits = DA7213_PLL_INDIV_36_TO_54_MHZ;
			indiv = DA7213_PLL_INDIV_36_TO_54_MHZ_VAL;
		} else {
			dev_err(component->dev,
				"PLL input clock %d above valid range\n",
				da7213->mclk_rate);
			return -EINVAL;
		}
		freq_ref = (da7213->mclk_rate / indiv);
	}

	pll_ctrl = indiv_bits;

	/* Configure PLL */
	switch (source) {
	case DA7213_SYSCLK_MCLK:
		snd_soc_component_update_bits(component, DA7213_PLL_CTRL,
				    DA7213_PLL_INDIV_MASK |
				    DA7213_PLL_MODE_MASK, pll_ctrl);
		return 0;
	case DA7213_SYSCLK_PLL:
		break;
	case DA7213_SYSCLK_PLL_SRM:
		pll_ctrl |= DA7213_PLL_SRM_EN;
		fout = DA7213_PLL_FREQ_OUT_94310400;
		break;
	case DA7213_SYSCLK_PLL_32KHZ:
		if (da7213->mclk_rate != 32768) {
			dev_err(component->dev,
				"32KHz mode only valid with 32KHz MCLK\n");
			return -EINVAL;
		}

		pll_ctrl |= DA7213_PLL_32K_MODE | DA7213_PLL_SRM_EN;
		fout = DA7213_PLL_FREQ_OUT_94310400;
		break;
	default:
		dev_err(component->dev, "Invalid PLL config\n");
		return -EINVAL;
	}

	/* Calculate dividers for PLL */
	pll_integer = fout / freq_ref;
	frac_div = (u64)(fout % freq_ref) * 8192ULL;
	do_div(frac_div, freq_ref);
	pll_frac_top = (frac_div >> DA7213_BYTE_SHIFT) & DA7213_BYTE_MASK;
	pll_frac_bot = (frac_div) & DA7213_BYTE_MASK;

	/* Write PLL dividers */
	snd_soc_component_write(component, DA7213_PLL_FRAC_TOP, pll_frac_top);
	snd_soc_component_write(component, DA7213_PLL_FRAC_BOT, pll_frac_bot);
	snd_soc_component_write(component, DA7213_PLL_INTEGER, pll_integer);

	/* Enable PLL */
	pll_ctrl |= DA7213_PLL_EN;
	snd_soc_component_update_bits(component, DA7213_PLL_CTRL,
			    DA7213_PLL_INDIV_MASK | DA7213_PLL_MODE_MASK,
			    pll_ctrl);

	/* Assist 32KHz mode PLL lock */
	if (source == DA7213_SYSCLK_PLL_32KHZ) {
		snd_soc_component_write(component, 0xF0, 0x8B);
		snd_soc_component_write(component, 0xF1, 0x03);
		snd_soc_component_write(component, 0xF1, 0x01);
		snd_soc_component_write(component, 0xF0, 0x00);
	}

	return 0;
}