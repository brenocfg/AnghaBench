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
struct ak4613_priv {unsigned int fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 129 
#define  SND_SOC_DAIFMT_LEFT_J 128 
 struct ak4613_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ak4613_dai_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct ak4613_priv *priv = snd_soc_component_get_drvdata(component);

	fmt &= SND_SOC_DAIFMT_FORMAT_MASK;

	switch (fmt) {
	case SND_SOC_DAIFMT_LEFT_J:
	case SND_SOC_DAIFMT_I2S:
		priv->fmt = fmt;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}