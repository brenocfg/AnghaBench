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
typedef  int u16 ;
struct cpcap_audio {int codec_clk_id; int codec_freq; int /*<<< orphan*/  regmap; TYPE_1__* component; } ;
typedef  enum cpcap_dai { ____Placeholder_cpcap_dai } cpcap_dai ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int CPCAP_BIT_CDC_CLK0 ; 
 int CPCAP_BIT_CDC_PLL_SEL ; 
 int CPCAP_BIT_CLK_IN_SEL ; 
 int CPCAP_BIT_ST_DAC_CLK0 ; 
 int CPCAP_BIT_ST_DAC_CLK_IN_SEL ; 
#define  CPCAP_DAI_HIFI 129 
#define  CPCAP_DAI_VOICE 128 
 int CPCAP_REG_CC ; 
 int CPCAP_REG_CDI ; 
 int CPCAP_REG_SDAC ; 
 int CPCAP_REG_SDACDI ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int cpcap_set_sysclk(struct cpcap_audio *cpcap, enum cpcap_dai dai,
			    int clk_id, int freq)
{
	u16 clkfreqreg, clkfreqshift;
	u16 clkfreqmask, clkfreqval;
	u16 clkidreg, clkidshift;
	u16 mask, val;
	int err;

	switch (dai) {
	case CPCAP_DAI_HIFI:
		clkfreqreg = CPCAP_REG_SDAC;
		clkfreqshift = CPCAP_BIT_ST_DAC_CLK0;
		clkidreg = CPCAP_REG_SDACDI;
		clkidshift = CPCAP_BIT_ST_DAC_CLK_IN_SEL;
		break;
	case CPCAP_DAI_VOICE:
		clkfreqreg = CPCAP_REG_CC;
		clkfreqshift = CPCAP_BIT_CDC_CLK0;
		clkidreg = CPCAP_REG_CDI;
		clkidshift = CPCAP_BIT_CLK_IN_SEL;
		break;
	default:
		dev_err(cpcap->component->dev, "invalid DAI: %d", dai);
		return -EINVAL;
	}

	/* setup clk id */
	if (clk_id < 0 || clk_id > 1) {
		dev_err(cpcap->component->dev, "invalid clk id %d", clk_id);
		return -EINVAL;
	}
	err = regmap_update_bits(cpcap->regmap, clkidreg, BIT(clkidshift),
				 clk_id ? BIT(clkidshift) : 0);
	if (err)
		return err;

	/* enable PLL for Voice DAI */
	if (dai == CPCAP_DAI_VOICE) {
		mask = BIT(CPCAP_BIT_CDC_PLL_SEL);
		val = BIT(CPCAP_BIT_CDC_PLL_SEL);
		err = regmap_update_bits(cpcap->regmap, CPCAP_REG_CDI,
					 mask, val);
		if (err)
			return err;
	}

	/* setup frequency */
	clkfreqmask = 0x7 << clkfreqshift;
	switch (freq) {
	case 15360000:
		clkfreqval = 0x01 << clkfreqshift;
		break;
	case 16800000:
		clkfreqval = 0x02 << clkfreqshift;
		break;
	case 19200000:
		clkfreqval = 0x03 << clkfreqshift;
		break;
	case 26000000:
		clkfreqval = 0x04 << clkfreqshift;
		break;
	case 33600000:
		clkfreqval = 0x05 << clkfreqshift;
		break;
	case 38400000:
		clkfreqval = 0x06 << clkfreqshift;
		break;
	default:
		dev_err(cpcap->component->dev, "unsupported freq %u", freq);
		return -EINVAL;
	}

	err = regmap_update_bits(cpcap->regmap, clkfreqreg,
				 clkfreqmask, clkfreqval);
	if (err)
		return err;

	if (dai == CPCAP_DAI_VOICE) {
		cpcap->codec_clk_id = clk_id;
		cpcap->codec_freq = freq;
	}

	return 0;
}