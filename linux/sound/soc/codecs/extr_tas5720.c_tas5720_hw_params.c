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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TAS5720_DIGITAL_CTRL1_REG ; 
 int /*<<< orphan*/  TAS5720_SSZ_DS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tas5720_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	unsigned int rate = params_rate(params);
	bool ssz_ds;
	int ret;

	switch (rate) {
	case 44100:
	case 48000:
		ssz_ds = false;
		break;
	case 88200:
	case 96000:
		ssz_ds = true;
		break;
	default:
		dev_err(component->dev, "unsupported sample rate: %u\n", rate);
		return -EINVAL;
	}

	ret = snd_soc_component_update_bits(component, TAS5720_DIGITAL_CTRL1_REG,
				  TAS5720_SSZ_DS, ssz_ds);
	if (ret < 0) {
		dev_err(component->dev, "error setting sample rate: %d\n", ret);
		return ret;
	}

	return 0;
}