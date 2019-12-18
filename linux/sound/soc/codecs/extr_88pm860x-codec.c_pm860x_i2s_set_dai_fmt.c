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
struct pm860x_priv {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char PCM_EXACT_I2S ; 
 unsigned char PCM_INF2_BCLK ; 
 unsigned char PCM_INF2_FS ; 
 unsigned char PCM_INF2_MASTER ; 
 unsigned char PCM_MODE_MASK ; 
 int /*<<< orphan*/  PM860X_CLK_DIR_IN ; 
 int /*<<< orphan*/  PM860X_CLK_DIR_OUT ; 
 int /*<<< orphan*/  PM860X_I2S_IFACE_2 ; 
#define  SND_SOC_DAIFMT_CBM_CFM 130 
#define  SND_SOC_DAIFMT_CBS_CFS 129 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 struct pm860x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned char,unsigned char) ; 

__attribute__((used)) static int pm860x_i2s_set_dai_fmt(struct snd_soc_dai *codec_dai,
				  unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct pm860x_priv *pm860x = snd_soc_component_get_drvdata(component);
	unsigned char inf = 0, mask = 0;

	mask |= PCM_INF2_BCLK | PCM_INF2_FS | PCM_INF2_MASTER;

	/* set master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		if (pm860x->dir == PM860X_CLK_DIR_OUT)
			inf |= PCM_INF2_MASTER;
		else
			return -EINVAL;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		if (pm860x->dir == PM860X_CLK_DIR_IN)
			inf &= ~PCM_INF2_MASTER;
		else
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		inf |= PCM_EXACT_I2S;
		break;
	default:
		return -EINVAL;
	}
	mask |= PCM_MODE_MASK;
	snd_soc_component_update_bits(component, PM860X_I2S_IFACE_2, mask, inf);
	return 0;
}