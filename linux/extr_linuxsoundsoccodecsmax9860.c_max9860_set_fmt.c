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
struct max9860_priv {unsigned int fmt; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 129 
#define  SND_SOC_DAIFMT_CBS_CFS 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 struct max9860_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max9860_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct max9860_priv *max9860 = snd_soc_component_get_drvdata(component);

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
	case SND_SOC_DAIFMT_CBS_CFS:
		max9860->fmt = fmt;
		return 0;

	default:
		return -EINVAL;
	}
}