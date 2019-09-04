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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct aif {int master; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 129 
#define  SND_SOC_DAIFMT_CBS_CFS 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline int set_aif_master_from_fmt(struct snd_soc_component *component,
		struct aif *aif, unsigned int fmt)
{
	int ret;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		aif->master = true;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		aif->master = false;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "Unsupported format (%d)\n", ret);
		return ret;
	}

	return 0;
}