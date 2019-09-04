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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FM_TDMCTL0_BDELAY ; 
 unsigned int R_PCMP2CTL0 ; 
 unsigned int R_PCMP3CTL0 ; 
 unsigned int R_TDMCTL0 ; 
#define  TSCS454_DAI1_ID 130 
#define  TSCS454_DAI2_ID 129 
#define  TSCS454_DAI3_ID 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int set_aif_tdm_delay(struct snd_soc_component *component,
		unsigned int dai_id, bool delay)
{
	unsigned int reg;
	int ret;

	switch (dai_id) {
	case TSCS454_DAI1_ID:
		reg = R_TDMCTL0;
		break;
	case TSCS454_DAI2_ID:
		reg = R_PCMP2CTL0;
		break;
	case TSCS454_DAI3_ID:
		reg = R_PCMP3CTL0;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev,
				"DAI %d unknown (%d)\n", dai_id + 1, ret);
		return ret;
	}
	ret = snd_soc_component_update_bits(component,
			reg, FM_TDMCTL0_BDELAY, delay);
	if (ret < 0) {
		dev_err(component->dev, "Failed to setup tdm format (%d)\n",
				ret);
		return ret;
	}

	return 0;
}