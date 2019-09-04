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
typedef  int /*<<< orphan*/  u8 ;
struct tlv320dac33_priv {unsigned int refclk; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC33_ASRC_CTRL_B ; 
 int /*<<< orphan*/  DAC33_INT_OSC_CTRL ; 
 int /*<<< orphan*/  DAC33_REFSEL ; 
 int /*<<< orphan*/  DAC33_SRCREFSEL ; 
#define  TLV320DAC33_MCLK 129 
#define  TLV320DAC33_SLEEPCLK 128 
 int /*<<< orphan*/  dac33_read_reg_cache (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac33_write_reg_cache (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct tlv320dac33_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int dac33_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	u8 ioc_reg, asrcb_reg;

	ioc_reg = dac33_read_reg_cache(component, DAC33_INT_OSC_CTRL);
	asrcb_reg = dac33_read_reg_cache(component, DAC33_ASRC_CTRL_B);
	switch (clk_id) {
	case TLV320DAC33_MCLK:
		ioc_reg |= DAC33_REFSEL;
		asrcb_reg |= DAC33_SRCREFSEL;
		break;
	case TLV320DAC33_SLEEPCLK:
		ioc_reg &= ~DAC33_REFSEL;
		asrcb_reg &= ~DAC33_SRCREFSEL;
		break;
	default:
		dev_err(component->dev, "Invalid clock ID (%d)\n", clk_id);
		break;
	}
	dac33->refclk = freq;

	dac33_write_reg_cache(component, DAC33_INT_OSC_CTRL, ioc_reg);
	dac33_write_reg_cache(component, DAC33_ASRC_CTRL_B, asrcb_reg);

	return 0;
}