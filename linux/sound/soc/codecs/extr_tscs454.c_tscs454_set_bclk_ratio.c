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
struct snd_soc_dai {int /*<<< orphan*/  id; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_I2SCMC_BCMP1 ; 
 int FB_I2SCMC_BCMP2 ; 
 int FB_I2SCMC_BCMP3 ; 
 unsigned int FM_I2SCMC_BCMP1 ; 
 unsigned int FM_I2SCMC_BCMP2 ; 
 unsigned int FM_I2SCMC_BCMP3 ; 
 unsigned int I2SCMC_BCMP_32X ; 
 unsigned int I2SCMC_BCMP_40X ; 
 unsigned int I2SCMC_BCMP_64X ; 
 int /*<<< orphan*/  R_I2SCMC ; 
#define  TSCS454_DAI1_ID 130 
#define  TSCS454_DAI2_ID 129 
#define  TSCS454_DAI3_ID 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int tscs454_set_bclk_ratio(struct snd_soc_dai *dai,
		unsigned int ratio)
{
	unsigned int mask;
	int ret;
	struct snd_soc_component *component = dai->component;
	unsigned int val;
	int shift;

	dev_dbg(component->dev, "set_bclk_ratio() id = %d ratio = %u\n",
			dai->id, ratio);

	switch (dai->id) {
	case TSCS454_DAI1_ID:
		mask = FM_I2SCMC_BCMP1;
		shift = FB_I2SCMC_BCMP1;
		break;
	case TSCS454_DAI2_ID:
		mask = FM_I2SCMC_BCMP2;
		shift = FB_I2SCMC_BCMP2;
		break;
	case TSCS454_DAI3_ID:
		mask = FM_I2SCMC_BCMP3;
		shift = FB_I2SCMC_BCMP3;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "Unknown audio interface (%d)\n", ret);
		return ret;
	}

	switch (ratio) {
	case 32:
		val = I2SCMC_BCMP_32X;
		break;
	case 40:
		val = I2SCMC_BCMP_40X;
		break;
	case 64:
		val = I2SCMC_BCMP_64X;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "Unsupported bclk ratio (%d)\n", ret);
		return ret;
	}

	ret = snd_soc_component_update_bits(component,
			R_I2SCMC, mask, val << shift);
	if (ret < 0) {
		dev_err(component->dev,
				"Failed to set DAI BCLK ratio (%d)\n", ret);
		return ret;
	}

	return 0;
}