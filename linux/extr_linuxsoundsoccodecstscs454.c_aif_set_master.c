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
 int ENODEV ; 
 unsigned int FM_I2SPCTL_PORTMS ; 
 unsigned int FV_PORTMS_MASTER ; 
 unsigned int FV_PORTMS_SLAVE ; 
 unsigned int R_I2SP1CTL ; 
 unsigned int R_I2SP2CTL ; 
 unsigned int R_I2SP3CTL ; 
#define  TSCS454_DAI1_ID 130 
#define  TSCS454_DAI2_ID 129 
#define  TSCS454_DAI3_ID 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static inline int aif_set_master(struct snd_soc_component *component,
		unsigned int aif_id, bool master)
{
	unsigned int reg;
	unsigned int mask;
	unsigned int val;
	int ret;

	switch (aif_id) {
	case TSCS454_DAI1_ID:
		reg = R_I2SP1CTL;
		break;
	case TSCS454_DAI2_ID:
		reg = R_I2SP2CTL;
		break;
	case TSCS454_DAI3_ID:
		reg = R_I2SP3CTL;
		break;
	default:
		ret = -ENODEV;
		dev_err(component->dev, "Unknown DAI %d (%d)\n", aif_id, ret);
		return ret;
	}
	mask = FM_I2SPCTL_PORTMS;
	val = master ? FV_PORTMS_MASTER : FV_PORTMS_SLAVE;

	ret = snd_soc_component_update_bits(component, reg, mask, val);
	if (ret < 0) {
		dev_err(component->dev, "Failed to set DAI %d to %s (%d)\n",
			aif_id, master ? "master" : "slave", ret);
		return ret;
	}

	return 0;
}