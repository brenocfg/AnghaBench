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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4641_BTIF ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_DSP_A 131 
#define  SND_SOC_DAIFMT_DSP_B 130 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 129 
#define  SND_SOC_DAIFMT_LEFT_J 128 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ak4641_pcm_set_dai_fmt(struct snd_soc_dai *codec_dai,
				  unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	u8 btif;
	int ret;

	/* interface format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		btif = (0x3 << 5);
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		btif = (0x2 << 5);
		break;
	case SND_SOC_DAIFMT_DSP_A:	/* MSB after FRM */
		btif = (0x0 << 5);
		break;
	case SND_SOC_DAIFMT_DSP_B:	/* MSB during FRM */
		btif = (0x1 << 5);
		break;
	default:
		return -EINVAL;
	}

	ret = snd_soc_component_update_bits(component, AK4641_BTIF, (0x3 << 5), btif);
	if (ret < 0)
		return ret;

	return 0;
}