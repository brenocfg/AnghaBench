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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int R01_SFORO_I2S ; 
 int R01_SFORO_LSB16 ; 
 int R01_SFORO_MASK ; 
 int R01_SFORO_MSB ; 
 int R01_SIM ; 
 unsigned int SND_SOC_DAIFMT_CBM_CFM ; 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LSB 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_MSB 128 
 int /*<<< orphan*/  UDA1380_IFACE ; 
 int uda1380_read_reg_cache (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uda1380_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int uda1380_set_dai_fmt_capture(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	int iface;

	/* set up DAI based upon fmt */
	iface = uda1380_read_reg_cache(component, UDA1380_IFACE);
	iface &= ~(R01_SIM | R01_SFORO_MASK);

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= R01_SFORO_I2S;
		break;
	case SND_SOC_DAIFMT_LSB:
		iface |= R01_SFORO_LSB16;
		break;
	case SND_SOC_DAIFMT_MSB:
		iface |= R01_SFORO_MSB;
	}

	if ((fmt & SND_SOC_DAIFMT_MASTER_MASK) == SND_SOC_DAIFMT_CBM_CFM)
		iface |= R01_SIM;

	uda1380_write(component, UDA1380_IFACE, iface);

	return 0;
}